#ifndef _MATRIX_H
#define _MATRIX_H

// error checking
#include <cassert>
// standard output with formatting
#include <iostream>
#include <iomanip>
// data structure
#include <vector>

// floating point tolerance
#define TOL 0.000001

using vec2 = std::vector<std::vector<double>>;

class Matrix {
private:
	vec2 data;
	size_t row;
	size_t column;

	void handleZero();// values smaller than TOL will become zero

public:
	// basic
	Matrix();
	Matrix(vec2 data);
	~Matrix();
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix operator*(double value);
	Matrix operator/(double value);
	void resize(size_t row, size_t column);
	double& value(size_t row, size_t column);

	// advanced
	Matrix minorMatrix(size_t row, size_t column);
	Matrix inverseMatrix();// uses adjoint matrix
	double determinant();// uses cofactor expansion
	double cofactor(size_t row, size_t column);
	void transpose();

	// utility
	void show(int minWidth = 1);
};

#endif