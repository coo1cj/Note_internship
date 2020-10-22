# Note--WEEK8

## static_cast<T>, dynamic_cast<T>, const_cast<T>, reinterpret_cast<T>

- static_cast<T>: 它可以用于类型之间的任何常规转换，依赖于静态（编译时）类型信息的转换。这包括数值类型之间的任何强制转换（例如：从short到int或从int到float）、指针和引用的强制转换（向上转换）。

- dynamic_cast<T>(expression): 该运算符把expression转换成T类型的对象。T必须是类的指针、类的引用或者void*；如果T是类指针类型，那么expression也必须是一个指针，如果T是一个引用，那么expression也必须是一个引用。它几乎专门用于处理多态性。它确保类型转换的结果是请求类的有效且完整的对象。确保我们是否安全地将一个对象的地址赋值给一个特殊的指针（类的向下转换时downcasting）。
  
```
class Widget{};
class SpecialWidget:public Widget{};
void update(SpecialWidget  *psw);

Widget * pw;
...

//如果pw所指的是SpecialWidget ，那么就传递过去；如果pw指的是Widget ，
//那么传递过去的值是null
update(dynamic_cast<SpecialWidget  *> (pw)); 
```

伟人曾经说过：
"The need for dynamic_cast generally arises because we want perform derived class operation on a derived class object, but we have only a pointer-or reference-to-base." -Scott Meyers

- const_cast<T>: 将变量的const属性去除。

- reinterpret_cast<T>: 好像基本上的类型转换都行（但是不是安全的, 在指针和指针之间（甚至是不相关的类）。允许所有指针转换：既不检查指向的内容也不检查指针类型本身。整型和指针之间的转换，函数指针之间的转换


## 关于头文件和源文件编译的一些问题
首先要明确的两点： 第一，#ifndefine #define #endif要解决的是防止重复包含的作用，相当于#program once。 第二，所有变量，非内联函数，类，结构体的定义必须符合[ODR](https://baike.baidu.com/item/ODR/22299478#:~:text=C%2B%2B%E5%8D%95%E5%AE%9A%E4%B9%89%E8%A7%84%E5%88%99,14882%EF%BC%892003%EF%BC%8C3.2%E8%8A%82%E3%80%82)（one definition rule）原则

如果在某个头文件中直接定义了一个函数，同时又有多个源文件包含这个头文件，在链接过程就会报错（一个函数存在多个定义），但如果是定义时加上了inline表示是内联函数则没有关系，此时，编译器在编译过程中会将内联函数用函数体直接代替，这样，在链接时就不会产生多个定义的错误。 但如果在头文件中只是声明了函数，在其中一个源文件中用inline定义了该函数，并在另一源文件中使用该函数则会发生函数未定义的报错。 原因是inline定义的函数只在本文件即翻译单元内有效，因此可以在不同的翻译单元中定义相同的内联函数（名称相同，函数内容不同）。

对于类的定义，类中所有的成员函数默认会加上inline修饰符，但展不展开是看编译器的心情了，关于虚函数加inline的问题（inline是编译时期的事情，而虚函数是在运行时绑定），是如果使用的对象没有用到多态则会调用inline，但大部分虚函数调用动作是通过对象的指针或引用完成的，此类行为无法被inlined。
