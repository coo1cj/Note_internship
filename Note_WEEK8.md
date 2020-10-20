## Note--WEEK8

static_cast<T>, dynamic_cast<T>, const_cast<T>, reinterpret_cast<T>

- static_cast<T>: 它可以用于类型之间的任何常规转换，依赖于静态（编译时）类型信息的转换。这包括数值类型之间的任何强制转换（例如：从short到int或从int到float）、指针和引用的强制转换（向上转换）。

- dynamic_cast<T>: 它只能与指向对象的指针和引用一起使用。它几乎专门用于处理多态性。它确保类型转换的结果是请求类的有效且完整的对象。确保我们是否安全地将一个对象的地址赋值给一个特殊的指针（类的向下转换时downcasting）。

伟人曾经说过：
"The need for dynamic_cast generally arises because we want perform derived class operation on a derived class object, but we have only a pointer-or reference-to-base." -Scott Meyers

- const_cast<T>: 将变量的const属性去除。

- reinterpret_cast<T>: 好像基本上的类型转换都行（但是不是安全的, 在指针和指针之间（甚至是不相关的类）。允许所有指针转换：既不检查指向的内容也不检查指针类型本身。整型和指针之间的转换，函数指针之间的转换
