#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

using Eigen::Matrix3d;
using Eigen::Vector3d;

inline void FirstExample() {
  std::cout << "------------- First Example -------------" << std::endl;

  MatrixXd m = MatrixXd::Random(3, 3);
  m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
  std::cout << "m =" << std::endl << m << std::endl;
  VectorXd v(3);
  v << 1, 2, 3;

  std::cout << "m * v =" << std::endl << m * v << std::endl;

  std::cout << "------------- First Example -------------" << std::endl
            << std::endl;
}

inline void SecondExample() {
  std::cout << "------------- Second Example ------------" << std::endl;

  Matrix3d m = Matrix3d::Random();
  m = (m + Matrix3d::Constant(1.2)) * 50;
  std::cout << "m =" << std::endl << m << std::endl;
  Vector3d v(1, 2, 3);

  std::cout << "m * v =" << std::endl << m * v << std::endl;

  std::cout << "------------- Second Example ------------" << std::endl
            << std::endl;
}

inline void ThirdExample() {
  std::cout << "------------- Third Example -------------" << std::endl;

  Eigen::MatrixXd m(2, 5);
  m.resize(4, 3);
  std::cout << "The matrix m is of size " << m.rows() << "x" << m.cols()
            << std::endl;
  std::cout << "It has " << m.size() << " coefficients" << std::endl;

  Eigen::VectorXd v(2);
  v.resize(5);
  std::cout << "The vector v is of size " << v.size() << std::endl;
  std::cout << "As a matrix, v is of size " << v.rows() << "x" << v.cols()
            << std::endl;

  std::cout << "------------- Third Example -------------" << std::endl
            << std::endl;
}