# Note WEEK5

### - 如何使用boost python中的numpy： 以下是根据boost numpy官方文档记录的测试代码

```
// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define BOOST_PYTHON_STATIC_LIB
#include <boost/numpy.hpp>
#include <boost/python.hpp>
#include <iostream>


namespace p = boost::python;
namespace np = boost::numpy;

struct UnarySquare {
	typedef double argument_type;
	typedef double result_type;

	double operator()(double r) const { return r * r; }
};

struct BinarySquare {
	typedef double first_argument_type;
	typedef double second_argument_type;
	typedef double result_type;

	double operator()(double a, double b) const { return (a * a + b * b); }

};







int main()
{
	Py_Initialize();
	np::initialize();

	/*uint8_t data[][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
	p::tuple shape = p::make_tuple(3, 2);
	p::tuple stride = p::make_tuple(sizeof(uint8_t) * 4, sizeof(uint8_t) );
	
	np::dtype dt = np::dtype::get_builtin<uint8_t>();
	np::ndarray mul_data_ex = np::from_data(data, dt,
		p::make_tuple(3, 4),
		p::make_tuple(4, 1),
		p::object());
	std::cout << "Original multi dimensional array :: " << std::endl
		<< p::extract<char const *>(p::str(mul_data_ex)) << std::endl;


	np::ndarray exp = np::from_data(data, dt, shape, stride, p::object());

	std::cout << p::extract<char const *>(p::str(exp)) << std::endl;*/

	int arr[] = { 1,2,3,4 };
	np::ndarray demo_array = np::from_data(arr, np::dtype::get_builtin<int>(),
											p::make_tuple(4),
											p::make_tuple(4),
											p::object());
	std::cout << "Demo array is " << p::extract<char const *>(p::str(demo_array)) << std::endl;

	/*demo_array[2] = 100;
	std::cout << "C++ array is: ";
	for (int i = 0; i < 4; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;*/

	p::object ud = p::class_<UnarySquare, boost::shared_ptr<UnarySquare>>("UnarySquare")
						.def("__call__", np::unary_ufunc<UnarySquare>::make());

	p::object inst = ud();
	std::cout << "Square of unary scalar 2.0 is " << p::extract<char const *>(p::str(inst.attr("__call__")(2.0))) << std::endl;

	p::object result_array = inst.attr("__call__")(demo_array);
	std::cout << "Square of demo array is " << p::extract<char const*>(p::str(result_array)) << std::endl;

	p::list l;
	l.append(2);
	l.append(7);

	ud = p::class_<BinarySquare, boost::shared_ptr<BinarySquare>>("BinarySquare")
		.def("__call__", np::binary_ufunc<BinarySquare>::make());
	inst = ud();
	std::cout << "Square of demo list is " << p::extract<char const*>(p::str(inst.attr("__call__")(l, l))) << std::endl;
	std::cout << "Square of demo array is " << p::extract<char const*>(p::str(inst.attr("__call__")(demo_array, demo_array))) << std::endl;
	


}

```


### - 如何在C++多线程中调用python： 找了很多资料，发现这方面的内容很少，官方文档解释的又不清楚，可以暂时看看这个链接 [解释](http://www.cppblog.com/API/archive/2013/12/06/204618.html) 
