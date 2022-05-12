# 简介
einsum（爱因斯坦求和）是pytorch、numpy中一个十分优雅的方法，如果利用得当，可完全代替所有其他的矩阵计算方法，不过这需要一定的学习成本。本文旨在详细解读einsum方法的原理，并给出一些基本示例。
# 问题引入
在线性代数中，我们最多涉及的是二阶及以下的张量．在这种情况下，纸面上可以很方便地写出低阶张量的矩阵形式，高阶的张量，它们的坐标就没法用矩阵表示．我们当然可以把矩阵拓展为立体阵等概念，但随着阶数上升，这种表示法的复杂程度几何级增加；我们也可以使用张量词条中所提过的向量矩阵的方法，比起立体阵要清楚一些，但套娃式的表达方式也对理解一个张量的性质造成了障碍．

**爱因斯坦求和约定**正是为了简洁地表达高阶张量的坐标运算而存在的．

## 一、矩阵乘法
假设 $A,B$ 矩阵大小分别是 $2*3$ 和 $3*2$ ，矩阵乘法的定义如下：
$$
[ \begin{array} { c c } { a _ { 1 1 } } & { a _ { 1 2 } } & { a _ { 1 2 } } \\ { a _ { 2 1 } } & { a _ { 2 2 } } & { a _ { 2 3 } } \end{array} ]*[ \begin{array} { c c } { b _ { 1 1 } } & { b _ { 1 2 } } \\ { b _ { 2 1 } } & { b _ { 2 2 } } \\ { b _ { 3 1 } } & { b _ { 3 2 } } \\ \end{array} ] = [ \begin{array} { c c } { c _ { 1 1 } } & { c _ { 1 2 } } \\ { c _ { 2 1 } } & { c _ { 2 2 } } \\ \end{array} ]
$$
其中，$C _ { i j } = \sum _ { k } A _ { i k } B _ { k j }$

用 `python` 循环实现：

```python
import numpy as np
np.random.seed(42)

A = np.random.rand(2, 3)
B = np.random.rand(3, 2)
M = np.zeros((2, 2))

for i in range(2):
    for j in range(2):
        for k in range(3):
            M[i, j] += A[i, k] * B[k, j]
print("Matrix A is: \n",A)
print("Matrix B is: \n",B)
print("M = A*B = \n",M)
```
结果为：

```bash
Matrix A is: 
 [[0.37454012 0.95071431 0.73199394]
 [0.59865848 0.15601864 0.15599452]]
Matrix B is: 
 [[0.05808361 0.86617615]
 [0.60111501 0.70807258]
 [0.02058449 0.96990985]]
M = A*B = 
 [[0.60831101 1.70756058]
 [0.13176846 0.78031684]]
```

## 二、爱因斯坦求和法

**爱因斯坦求和是一种对求和公式简洁高效的记法，其原则是当变量下标重复出现时，即可省略繁琐的求和符号。**

比如求和公式：

$$
\sum_{i=1}^n a_{i} b_{i} = a_{1} b_{1} + a_{2} b_{2} + ... + a_{n} b_{n}
$$

其中变量 **a** 和变量 **b** 的下标重复出现，则可将其表示为：

$$
a_{i} b_{i} = \sum_{i=1}^n a_{i}
$$

由此我们可以将上述矩阵运算化简为：

$$
C_ { i j } = \sum _ { k } A _ { i k } B _ { k j } = A _ { i k } B _ { k j }
$$

进一步地，我们可以得到矩阵乘法的一个抽象

$$
ik * kj = ij
$$

# einsum的原理
## 一、具体原理

einsum方法正是利用了爱因斯坦求和简洁高效的表示方法，从而可以驾驭任何复杂的矩阵计算操作。基本的框架如下：

~~~
C = einsum('ij,jk->ik', A, B)
~~~

上述操作表示矩阵A与矩阵B的点积。输入的参数分为两部分:

+ 前面表示计算操作的指令串，
+ 后面是以逗号隔开的操作对象（数量需与前面对应）。

其中在计算操作表示中，

+ "->" 左边是以逗号隔开的下标索引，重复出现的索引即是需要爱因斯坦求和的；
+ "->" 右边是最后输出的结果形式。

以上式为例，其计算公式为：$C_{ik} = \sum_{j} A_{ij} B_{jk}$ ，其等价于矩阵A与B的点积。

在矩阵之间的运算中，下标可以分为两类：

+ 自由标(Free index)，也就是在输入和输出端都出现的下标
+ 哑标(Summation index)，在输入端出现但输出端没有出现的下标

矩阵运算中所有参与运算的下标都被包含在次定义中。

以上述矩阵 $A,B$ 的乘法过程为例：

```python
C = np.einsum("ik,kj->ij", A, B)
print("einsum result is :\n", C)
print("M = A*B = \n",M)
```

可以看出，这与上述通过循环方式得出的结果一致。在 `ij,jk -> ik` 的例子中, `i,j ` 是自由标，`k` 是哑标。

## 二、计算准则
1. 两个不同矩阵相乘，**哑标**维度需要逐元素相乘并求和，**自由标**保留
2. 自由标可在输出中以任意顺序出现，但只能出现一次

这是两条基本准则，具体的计算场景可以参考下文实例。
## 三、典型计算场景
利用einsum求解张量运算主要分为单操作数和多操作数的情况，我们分别讨论，并力图转化为循环形式便于明晰求解过程。
### 1. 单操作数
####  1.1 矩阵的迹：
迹（trace）指的是方针的对角线元素。
einsum表示为：
~~~python
m = np.matrix([
    [1,2,3],
    [4,5,6],
    [7,8,9]
])
M=np.einsum("ii -> i", m)
print("Trace of m is :",M)
~~~
结果：

```bash
Trace of m is : [1 5 9]
```

#### 1.2 矩阵转置
矩阵的转置（transpose）指矩阵行列互换。
einsum表示为：
~~~python
x = np.random.rand(2, 3)
M=np.einsum("ij -> ji", x)
print("origin x is :\n",x)
print("transpose of x is :\n",M)
~~~
结果：

```bash
origin x is :
 [[0.43194502 0.29122914 0.61185289]
 [0.13949386 0.29214465 0.36636184]]
transpose of x is :
 [[0.43194502 0.13949386]
 [0.29122914 0.29214465]
 [0.61185289 0.36636184]]
```

#### 1.3 矩阵求和
按行还是列求和，取决于最终保留的下标：
~~~python
m = np.matrix([
    [1,2,3],
    [4,5,6],
    [7,8,9]
])
m_r = np.einsum("ij -> i", m) #按行求和
m_c = np.einsum("ij -> j", m) #按列求和
m_a = np.einsum("ij -> ", m) #全部求和
print("按行求和：\n",m_r)
print("按列求和：\n",m_c)
print("全部求和：\n",m_a)
~~~
结果：
```bash
按行求和：
 [ 6 15 24]
按列求和：
 [12 15 18]
全部求和：
 45
```
### 2. 多操作数
#### 2.1 向量内/外积
~~~python
a = np.array([1,2])
b = np.array([1,3,5])
c = np.array([3,4])

## 内积
inner = np.einsum("i, j ->", a, c)
## 外积
exter = np.einsum("i, j -> ij", a, b) 

print("{0} 与 {1} 内积： {2}".format(a,c,inner))
print("{0} 与 {1} 外积：\n{2}".format(a,b,exter))
~~~
结果：

```bash
[1 2] 与 [3 4] 内积： 21
[1 2] 与 [1 3 5] 外积：
[[ 1  3  5]
 [ 2  6 10]]
```
#### 2.2 矩阵乘法
矩阵乘法最典型的形式为：
~~~python
A = np.random.rand(3, 5)
B = np.random.rand(5, 2)
M = np.einsum("ik, kj -> ij", A, B) # 3*2
~~~
它的循环形式可以展开为：
~~~python
M = np.zeros((3, 2))
for i in range(3):
    for j in range(2):
        for k in range(5):
            M[i, j] += A[i, k] * B[k, j]
~~~
当k也作为自由标被保留下来的时候，情况稍有不同：
~~~python
M = np.einsum("ik, kj -> ijk", A, B)
~~~
此时，上式对应的循环形式应该为：
~~~python
A = np.random.rand(3, 5)
B = np.random.rand(5, 2)
M = np.empty((3, 2, 5))

for i in range(3):
    for j in range(2):
        for k in range(5):
            M[i, j, k] = A[i, k] * B[k, j]
~~~
此时，k不在作为哑标被求和，在输出中也会保留该维度，并且按照 `ijk` 的顺序排列输出维度。

多个矩阵的连乘可以按照同样的方式进行：
~~~python
x = np.random.rand(2, 3)
y = np.random.rand(3, 5)
z = np.random.rand(5, 2)
m = np.einsum("ij, jk, kl -> il", x, y, z)
print(m.shape)

## (2,2)
~~~
### 3. 广播乘法
广播方式比较复杂，这里仅举一个常见例子：

在 Transformer 的 self-attention 机制中，对与子矩阵 $QKV$ 需要进行 Multi-Head 操作，
这里假设：`
batch=32,
max_sequence=20,
Heads=8,
d_model=512
`

转化为多头后，维度变为：`512 // 8 = 64`，可以得到 $Q,K$ 矩阵的张量表示：
~~~python
Q = numpy.random.rand(32, 20, 8, 64)
K = numpy.random.rand(32, 20, 8, 64)

M=np.einsum("nqhd,nkhd->nhqk", Q, K) 
print(M.shape)

# （32, 8, 20 ,20)
~~~
通过这种方法，可以轻松完成多头下的自注意力乘积操作。

实际上，上述操作与下面的过程也是等价的：
~~~python
Q=Q.transpose(0,2,1,3) # nqhd -> nhqd
K=K.transpose(0,2,1,3) # nkhd -> nhkd
M=np.einsum('nhqd, nhkd->nhqk', A,B) # （32, 8, 20 ,20)
print(M)
~~~
另外，广播乘法有一个更简洁的形式：
~~~python
M = np.einsum('...qd, ...kd->...qk', A,B) 
# （32, 8, 20 ,20)
~~~
`...`指代任意多个维度，这在处理batch和图像中的多通道时尤为有效。
### 参考链接：
+ [einsum详解：一个函数包揽张量乘法](https://blog.csdn.net/qq_38056431/article/details/123033994)
+ [einsum方法详解（爱因斯坦求和）](https://blog.csdn.net/ashome123/article/details/117110042)
+ [爱因斯坦求和约定](https://wuli.wiki/online/EinSum.html)
+ [A basic introduction to NumPy's einsum](https://ajcr.net/Basic-guide-to-einsum/)
