### *C++ 中的左值和右值*： 区分 是否在内存空间中有地址。 左值是能找到地址的（用取地址符&），而右值不行。 

右值的例子： 比如函数的返回值 int Foo(){ return 2; } 其中 Foo（）函数的返回值就是一个*右值*，因此 Foo() = 2是不允许的。 但如果情况如下所示：

```
int a = 0; //全局变量 a

struct x{
  int a,
  .....   // 很多其他数据
};

int& Foo() {
  return a;
}

x F(){
  ...
  return x;
}

int main()
{
    foo() = 10;
    return 0;
}
```
这里 foo 返回一个*引用*。引用一个左值，因此可以赋值给它。 但如果a不是*全局变量*而是函数内的*局部变量*，这样是不可以的！！！ 因为这种情况下的返回值引用当*函数返回时，栈的内容已经不存在了，引用会指向不知道的地方，很危险。*

因此只能返回整个类型，但如果返回值是个类或者自定义结构体，里面有指向资源的指针，在返回赋值时又进行了拷贝赋值，这样会很影响效率，影响程序的性能。 因此我们可以使用引用(*因为是引用，就避免了拷贝*)来接受这个返回值, const x& f = F()， 这里const是*必须*的。

为什么？ 因为如果没有const， 其引用只能被左值给赋值，而不能是右值。  本来F()的返回值是一个临时的变量，在它调用结束后，就应该销毁了。可是通过像这样const x& f = F();，*把临时的返回值赋值给一个const左值引用，F()返回值并不会立即销毁。这等于是在const引用的作用域内，延长了F()返回值的存活时间。*

所以就出现了右值引用 x&& f = F(), 这样就是可以的。 而且，右值引用本身是一个左值，所以左值引用可以指向一个右值引用

对于 x f = F() 之前说了如果编译器没有优化，会直接将F()返回的临时变量拷贝赋值给f，非常消耗性能。 因此用右值引用就避免了拷贝，但在使用之前，需要定义一个搬移构造函数（move constructor，也叫移动构造函数）。和拷贝构造函数x(x&)不一样的是，搬移构造函数接受的是一个右值引用：x(x&&)

这样一来如果是从一个临时变量来构造新的x的话，编译器会优先调用搬移构造函数。 C++11提供了std::move来废弃一个对象，也就是把它标识为临时变量，这样可以丢给搬移构造函数处理。

*实际上std::move不能移动任何东西，因为移动赋值是通过对操作符=的重载（参数是右值引用）来实现的，move函数只是把一个左值强制转换成右值引用，继而使用右值引用来使用该值，功能类似于static_cast<T&&>lvalue*

x的类型是右值引用，指向一个右值，但x本身是左值还是右值呢？  既可以是左值也可以是右值，区分是是否有变量名，若有名则是左值，否则是右值

比较好的参考网站[这里](https://www.bogotobogo.com/cplusplus/C11/5_C11_Move_Semantics_Rvalue_Reference.php)


### 以下是网上的例子以及个人对string类的编写

```
// Test_shared_ptr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <iostream>
#include <string>

using namespace std;

int& foo() {
	int a = 2;
	return a;
}


class Intvec
{
public:
	explicit Intvec(size_t num = 0)
		: m_size(num), m_data(new int[m_size])
	{
		log("constructor");
	}

	~Intvec()
	{
		log("destructor");
		if (m_data) {
			delete[] m_data;
			m_data = 0;
		}
	}

	Intvec(const Intvec& other)
		: m_size(other.m_size), m_data(new int[m_size])
	{
		log("copy constructor");
		for (size_t i = 0; i < m_size; ++i)
			m_data[i] = other.m_data[i];
	}

	Intvec& operator=(const Intvec& other)
	{
		log("copy assignment operator");
		Intvec tmp(other);
		std::swap(m_size, tmp.m_size);
		std::swap(m_data, tmp.m_data);
		return *this;
	}
private:
	void log(const char* msg)
	{
		cout << "[" << this << "] " << msg << "\n";
	}

	size_t m_size;
	int* m_data;
};


class myString {
	size_t length;
	char* data;
public:
	myString(): length(0), data(NULL) {}

	myString(const char* str) {
		cout << "[" <<  this << "]" << "Constructer is called " << endl;
		/*int i = 0;
		while (!str) {
			data[i] = *str;
			i++;
			str++;
		}
		length = i;*/
		
		length = strlen(str);
		data = new char[length + 1];
		memcpy(data, str, length);
	}

	// Copy
	myString(const myString& str) {
		cout << "[" <<  this << "]" << "Copy constructer is called " << endl;
		this->data = str.data;
		this->length = str.length;
	}

	myString& operator=(const myString& str) {
		cout <<  "[" << this << "]" << "Copy assignment constructer is called " << endl;
		if (this != &str) {
			if (this->data) {
				delete data;
				this->data = NULL;
			}
			this->length = str.length;
			this->data = new char[str.length + 1];
			memcpy(this->data, str.data, this->length);
		}
		return *this;
	}

	// Move
	myString(myString&& str) {
		cout << "[" << this << "]" << "Move constructer is called " << endl;
		this->data = str.data;
		this->length = str.length;
		str.data = NULL;
	}

	myString& operator=(myString&& str) {
		cout << "[" << this << "]" << "Move assignment is called " << endl;
		if (this != &str) {
			this->data = str.data;
			this->length = str.length;
			str.data = NULL;
		}
		return *this;
	}

	~myString() {
		cout << "[" << this << "]" << "Destructer is called " << endl;
		if(data)
			delete data; 
		data = 0; 
	}

	char operator[](int pos) const {
		return *(data + pos);
	}




	friend ostream& operator<<(ostream& out, myString& str) {
		for (int i = 0; i < str.length; i++) {
			cout.put(str[i]);
		}

		return out;
	}


};





int main()
{
	/*Intvec v1(20);
	Intvec v2;

	cout << "assigning lvalue...\n";
	v2 = v1;
	cout << "ended assigning lvalue...\n";


	std::string x1 = "hello, world!";
	std::string x2 = std::move(x1);
	cout << "x1 = " << x1 << endl;
	cout << "x2 = " << x2 << endl;*/

	myString str = "qsdqsd";
	myString s1 = move(str);

	myString s;
	cout << sizeof(str) << endl;
	cout << sizeof(s1) << endl;
	cout << sizeof(s) << endl;
	cout << s1 << endl;
	cout << s << endl;

}

```
