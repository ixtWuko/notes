# Python Numpy

```python
import numpy as np

# 创建
mat_zeros = np.zeros((3, 4))
mat_ones = np.ones((3, 4))
mat_rand = np.random.random((3, 4))
mat_eye = np.eye(4)
mat_diag = np.diag([1, 2, 3, 4])  # 对角元素

mat = np.array(range(12)).reshape(3, 4)
print('mat: ', mat)
print("mat's size: ", mat.shape, mat.size)

# 运算
print(mat < 5)
print(mat + 2, mat + mat_ones, sep='\n')
print(mat * 2, mat * mat, mat**3, sep='\n')
print(mat.dot(mat_ones.T), mat @ mat_ones.T, sep='\n')  # 矩阵乘法

# absolute, sign, sqrt, exp, log, ceil, floor
# sin, cos, tan, arcsin, arccos, arctan, deg2rad, rad2deg
# conj, real
print(np.sqrt(mat))
# all, any
# max, argmax, min, argmin
# round,
# mean, var, std
# sum, prod
print(mat_rand.sum(), mat_rand.sum(axis=0))

print(mat.diagonal())  # 对角元素向量
print(np.trace(mat))  # 迹，对角元素之和
print(mat.transpose(), mat.T, sep='\n')  # 转置
print(np.linalg.inv(mat_eye))  # 逆
print(np.linalg.det(mat))  # 行列式
print(np.linalg.eig(mat_eye))  # 特征值，特征向量
print(np.linalg.svd(mat_eye))  # SVD分解
print(np.linalg.solve(mat_eye, [1, 2, 3, 4]))  # 解
# 对于向量还有
# np.linalg.inner(v1, v2)  内积 np.dot
# np.linalg.outer(v1, v2)  外积 np.cross


# 堆叠
print(np.vstack((mat, mat_zeros)))
print(np.hstack((mat, mat_zeros)))

mat_view = mat.view()  # 共享数据，但可以不同形状
mat_copy = mat.copy()  # 深拷贝

np.fromestring(string, dtype=np.uint8)
```