// 4Thread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <iostream>
#include <stack>
#include <mutex>
#include <memory>
#include <exception>
#include <future>
#include <utility>

using namespace std;

void F( int i ) {
	for (int x = 0; x < i; x++) {
		cout << "it's the function F\n";
	}
}

class A {
public:
	void operator()(int i) {
		for (int j = 0; j < i; j++) {
			cout << "it's the class A member function Fo\n" ;
		}
	}
};

struct task {
	int &i;
	task(int &ii) : i(ii) { cout << "task constructor\n"; }
	void operator()() {
		for (int j = 0; j < 10; j++) {
			cout << i << "\n";
		}
	}

};


class RAII_task {
	thread t;
public:
	RAII_task(thread& tt) : t(move(tt)) { cout << "raii_task constructor\n"; }
	~RAII_task() {
		if (t.joinable()) {
			t.join();
		}
		cout << "raii_task destructor\n";
	}
	RAII_task(const RAII_task& r) = delete;
	RAII_task& operator=(RAII_task& r) = delete;

};


void full() {
	int state = 10;
	task tt(state);
	thread t(tt);
	//RAII_task r(t);  
	t.join();    //这里如果在join之前发生了exception，线程会执行操作超出范围的tt.i，会有危险。 所以需要将task包装一下，用上一行的RAII_task, 也就是在离开此函数时raii_task会执行析构函数，使得线程能顺利完成


}



struct empty_stack : std::exception {
	const char* what() const throw();
};




/* 建立一个线程安全的stack 因为STL提供的一些接口并不是线程安全的 */
/* 其中关于pop函数，为什么会有两个函数，因为pop的操作是先用top函数取出栈顶值，再把栈顶值给删去。(即把原本的两个接口函数合并在了一起）如果分开的话，线程并发访问时，可能会发生问题，一个线程已取出栈中最后一个元素而另一个线程再使用top就会出错 */
/* 而两个pop函数中不用值返回的原因是当值返回时，会发生一次拷贝，涉及到空间的开辟和复制，在这时就有可能发生内存空间不足导致的错误，这时就产生了两种解决方案。 一个是传递引用，也就是在调用函数前应事先存在一个对象。另一个就是返回一个智能指针，操作方便 */
template<typename T>
class ThreadSafe_stack {
	stack<T> s;
	mutex m;
public:
	ThreadSafe_stack(){}
	ThreadSafe_stack(const ThreadSafe_stack& other) {
		lock_guard<mutex> guard(other.m);
		s = other.s;
	}
	ThreadSafe_stack& operator=(const ThreadSafe_stack& other) = delete;

	bool empty() {
		lock_guard<mutex> guard(m);
		return s.empty();
	}

	void pop(T& value) {
		lock_guard<mutex> guard(m);
		if (s.empty()) throw empty_stack();
		value = s.top();
		s.pop();
	}

	shared_ptr<T> pop() {
		lock_guard<mutex> guard(m);
		if (s.empty()) throw empty_stack();

		shared_ptr<T> ptr(make_shared<T>(s.top()));
		s.pop();
		return ptr;
	}

	void push(T value) {
		lock_guard<mutex> guard(m);
		s.push(value);
	}

};

void initiazer(promise<shared_ptr<int>>& promiseObj, ThreadSafe_stack<int>& ts) {
	shared_ptr<int> ptr(ts.pop());
	promiseObj.set_value(ptr);
}




int main()
{
	/*auto Foo = [](int x) {
		for (int j = 0; j < x; j++) {
			cout << "it's from the lambda function\n";
		}
	};
	thread t(A(), 5);*/
	//cout << &Foo << endl;
	/*thread t1(F, 3);
	thread t2(A(), 3);
	thread t3(Foo, 3);

	t1.join();
	t2.join();
	t3.join();
	cout << "it's from the main thread" << endl;*/
	//full();

	
	ThreadSafe_stack<int> ts;
	promise<shared_ptr<int>> pro;
	future<shared_ptr<int>> futureObj = pro.get_future();
	
	
	thread t1(&ThreadSafe_stack<int>::push, &ts, 1);
	//thread t3(&ThreadSafe_stack<int>::pop, &ts);
	thread t2(&ThreadSafe_stack<int>::push, &ts, 55);
	thread t(initiazer, ref(pro), ref(ts));   //让另一个线程来获取pop函数的返回值，并将结果返回给主线程，主线程可以通过future.get（）获取

	
	t1.join();
	t2.join();
	//t3.join();
	t.join();
	cout << "here :" << *((futureObj.get()).get()) << endl;
	int value = 0;
	while (!ts.empty()) {
		ts.pop(value);
		cout << value << endl;
	}


    return 0;
}

const char * empty_stack::what() const throw()
{
	return "this stack is empty !";
}
