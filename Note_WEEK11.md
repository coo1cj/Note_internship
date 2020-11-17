# Note WEEK11

### It's about sth reading notes

因为现在公司给了一个比较长时间的项目，而且又和之前做的东西很相似，所以暂时没有什么太多可做的notes。就写一些平时不太注意但又重要的基础吧

- 在new 和 delete中，当delete[]释放一个动态数组的时候，会先销毁指针所指的数组元素，并释放对应的内存。其中重要的是它会先销毁数组的最后一个元素，然后再往前，称为逆序销毁

- 在用delete销毁一个动态数组或者是用delete[] 销毁一个单一对象的时候，这样的操作是未定义的。也就是编译器不会给出警告，但是在程序执行过程中可能会出现异常。

- 可以用智能指针unique_ptr指向一个动态数组 unique_ptr<T[]> up, 此时指向动态数组的unique_ptr不能使用箭头或点运算符。 shared_ptr不支持管理动态数组，如果要想用shared_ptr管理动态数组，就必须提供自己定义的删除器 如： shared_ptr<int> sp(new int[10], [](int* p){ delete[] p;}); sp.reset(); 此时会使用我们提供的lambda删除器，delete动态数组. 若未提供删除器，则这段代码是为定义的，因为默认情况下shared_ptr是用delete销毁所指的对象的。

- allocator分配器在头文件memory当中，它将new分配的动态数组时的内存分配和构造对象分离开来，同时allocator也是一个模版。它提供一种类型感知的内存分配，它分配的内存是原始的，未构造的。 如allocator<string> alloc; auto p = alloc.allocate(n); 分配n个未初始化的string,返回指向该内存的指针

- C++是否将符号写入目标文件是看该定义或声明具有外部链接还是内部链接，如果具有内部链接则不会将导入符号写入目标文件，那么链接器也就不会去寻找其定义或实现。 
