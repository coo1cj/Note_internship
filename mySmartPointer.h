#pragma once
#include <iostream>
template<typename T>
class mySmartPointer;

template<typename T>
class U_ptr {
private:
	friend class mySmartPointer<T>;
	U_ptr() = default;
	U_ptr(T *p) : ptr(p), count(1){}
	~U_ptr() { delete ptr; }

	T *ptr;
	int count;
};

template<typename T>
class mySmartPointer {
	U_ptr<T>* ptr;

public:
	mySmartPointer(T* ptr): ptr(new U_ptr<T>(ptr)) {}
	mySmartPointer(const mySmartPointer<T>& sp) {
		++sp.ptr->count;
		ptr = sp.ptr;
	}
	mySmartPointer& operator=(const mySmartPointer<T>& sp) {
		if (--ptr->count == 0)
			delete ptr;
		++sp.ptr->count;
		ptr = sp.ptr;
		return *this;
	}
	~mySmartPointer() {
		--ptr->count;
		if (ptr->count == 0)
			delete ptr;
		else
			std::cout << "there are also " << ptr->count << " smartpointer point to the object" << std::endl;
	}

	T& operator* () {
		return *(ptr->ptr);
	}

	T* operator ->() {
		return ptr->ptr;
	}

};


class Point {
	int x, y;
public:
	Point(int x = 0, int y = 0): x(x), y(y) {}

	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	int getX() const { return x; }
	int getY() const { return y; }

	~Point() { std::cout << "Point dtor" << std::endl; }
};
