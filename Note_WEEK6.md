## WEEK6

#### 真是不容易的一周，摸鱼了两周这周才真正开始搞新版本的问题。 其中包含了对boost的下载编译等等，最初下载了boost 1.74，按照教程一步步搞非常简单明了，奈何tut说公司要用的是boost 1.55。 伤心，硬着头皮做，结果发现问题太多了，果然老版本的库都有着这样那样的问题

#### 其中最让人头疼的是为什么在编译boost python 3.8版本的时候怎么都编译不成功，我TM搜了两天资料，终于在这周的最后一天找到了问题所在！ 多亏了这个[该死的boost](https://stackoverflow.com/questions/54991157/cant-compile-boost-python-1-65-1-with-msvc2015)， 虽然这是关于boost 1.65的，但是和我的问题一样， 都是因为builtin_converters.cpp出错了

#### [解决方案](https://github.com/boostorg/python/commit/660487c43fde76f3e64f1cb2e644500da92fe582) 从stackoverflow的回复者中我们可以看到，当遇到某个文件出问题时，特别是你觉得可能是版本问题时，就可以去git相应的commit history中去看看，或者看看git blame of the relevant file。

#### 第二个问题就是，我先编译的boost 1.74，其中python编译完之后是会有boost_numpy38-vc120-mt-x64-1_74.lib这玩意儿的，但是在boost 1.55的时候没有，我一度以为我一定是哪里出了问题。结果最后，WTF，*Boost.NumPy is an extension for Boost.Python < v1.63 that adds NumPy support.* 我日你大爷的，也就是说在boost 1.63之前就不提供numpy支持，还得自己下载编译咯!  [传送门](https://github.com/ndarray/Boost.NumPy)

#### 还有一个问题就是困扰了我一周，就是关于将python解释器embedded入C++的多线程程序中，我也搜了很多资料，中文的一塌糊涂，唯一能看的[但比较老了](http://www.cppblog.com/API/archive/2013/12/06/204618.html)
