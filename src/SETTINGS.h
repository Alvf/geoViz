#ifndef SETTINGS_H
#define SETTINGS_H

#include "Eigen/Dense"
#include "Eigen/Sparse"
#include "Eigen/Geometry"

using namespace Eigen;

typedef Matrix<double, 2, 2 > MATRIX2;
typedef Matrix<double, 3, 3 > MATRIX3;
typedef Matrix<double, 2, 3 > MATRIX2x3;
typedef Matrix<double, 3, 2 > MATRIX3x2;
typedef Matrix<double, 4, 4 > MATRIX4;
typedef Matrix<double, 4, 3 > MATRIX4x3;
typedef Matrix<double, 4, 2 > MATRIX4x2;
typedef Matrix<double, 6, 6 > MATRIX6;
typedef Matrix<double, 16, 16> MATRIX16;
typedef Matrix<double, 16, 20> MATRIX16x20;
typedef Matrix<double, 20, 20> MATRIX20;

typedef Matrix<double, 2, 1 > VEC2;
typedef Matrix<double, 3, 1 > VEC3;
typedef Matrix<double, 4, 1 > VEC4;
typedef Matrix<double, 16, 1> VEC16;
typedef Matrix<double, 20, 1> VEC20;

typedef Matrix<int, 3, 1 > VEC3I;
typedef Matrix<int, 4, 1 > VEC4I;
typedef Matrix<int, 5, 1 > VEC5I;

typedef Matrix<std::complex<double>, 3, 1 > VEC3C;

typedef Matrix<double, Dynamic, Dynamic> MATRIX;
typedef Matrix<double, Dynamic, 1> VECTOR;
typedef Eigen::SparseMatrix<double> SPARSE_MATRIX;
typedef Eigen::Triplet<double> TRIPLET;

#ifndef NDEBUG
#define NDEBUG
#endif

#endif
