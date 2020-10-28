# WEEK9 Note

### STL容器，algorithm算法， template模版 关系： 容器使得算法独立于数据结构，而模版使得算法独立于数据类型。 讲白了这就是容器和模版所解决的问题。

STL容器
- 关联容器
  - set： 不提供下标操作
  - map：
  - multiset： 一个key可以对应多个实例， 仅有key_type， key_type和value_type是相同的
  - multimap： 一个key可以对应多个实例
- 序列容器：按一定顺序存储
  - vector
  - list
  - deque
