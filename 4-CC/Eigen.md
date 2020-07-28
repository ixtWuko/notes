```cpp
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

MatrixXd mat(3,4);
VectorXi vec(5);

MatrixXf::Zero(3, 4); // 全零矩阵
MatrixXf::Constant(2, 4, 1.0); // 临时的矩阵

mat(1,1)；
mat.block(1,1,2,3) // block
mat.row(1); // 行
mat.col(1); // 列

vec.dot(vec);
vec.cross(vec);
mat * mat;  // 矩阵乘法
// ArrayXXd 类型的此形式为对应元素相乘

mat.sum(); // prod, mean，minCoeff, maxCoeff, trace, norm 平方和的根
mat.transpose(); // mat^T
mat.adjoint(); // mat^*
mat.determinant(); // |mat|
mat.inverse(); // mat^-1


```