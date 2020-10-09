### WEEK6

#### 真是不容易的一周，摸鱼了两周这周才真正开始搞新版本的问题。 其中包含了对boost的下载编译等等，最初下载了boost 1.74，按照教程一步步搞非常简单明了，奈何tut说公司要用的是boost 1.55。 伤心，硬着头皮做，结果发现问题太多了，果然老版本的库都有着这样那样的问题

#### 其中最让人头疼的是为什么在编译boost python 3.8版本的时候怎么都编译不成功，我TM搜了两天资料，终于在这周的最后一天找到了问题所在！ 多亏了这个[该死的boost](https://stackoverflow.com/questions/54991157/cant-compile-boost-python-1-65-1-with-msvc2015)， 虽然这是关于boost 1.65的，但是和我的问题一样， 都是因为builtin_converters.cpp出错了

#### [解决方案](https://github.com/boostorg/python/commit/660487c43fde76f3e64f1cb2e644500da92fe582)
