#include "matrix.h"

Matrix::Matrix() : row(0), column(0) {

}

Matrix::Matrix(vec2 data) : data(data), row(data.size()), column(data[0].size()) {

}

Matrix::~Matrix() {

}

Matrix::Matrix(const Matrix& other) : Matrix(other.data) {

}

Matrix& Matrix::operator=(const Matrix& other) {
	data = other.data;
	return *this;
}

Matrix Matrix::operator+(const Matrix& other) {
	assert(row == other.row && "row size mismatch");
	assert(column == other.column && "row size mismatch");
	Matrix rtn(data);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < other.column; j++) {
			rtn.data[i][j] += other.data[i][j];
		}
	}
	rtn.handleZero();
	return rtn;
}

Matrix Matrix::operator-(const Matrix& other) {
	assert(row == other.row && "row size mismatch");
	assert(column == other.column && "row size mismatch");
	Matrix rtn(data);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < other.column; j++) {
			rtn.data[i][j] -= other.data[i][j];
		}
	}
	rtn.handleZero();
	return rtn;
}

Matrix Matrix::operator*(const Matrix& other) {
	assert(column == other.row && "size mismatch");
	Matrix rtn;
	rtn.resize(row, other.column);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < other.column; j++) {
			rtn.data[i][j] = 0;
			for (int k = 0; k < column; k++) {
				rtn.data[i][j] += data[i][k] * other.data[k][j];
			}
		}
	}
	rtn.handleZero();
	return rtn;
}

Matrix Matrix::operator*(double value) {
	Matrix rtn(data);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			rtn.data[i][j] *= value;
		}
	}
	rtn.handleZero();
	return rtn;
}

Matrix Matrix::operator/(double value) {
	assert(value != 0 && "devide by zero");
	Matrix rtn(data);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			rtn.data[i][j] /= value;
		}
	}
	rtn.handleZero();
	return rtn;
}

void Matrix::resize(size_t row, size_t column) {
	this->row = row;
	this->column = column;
	data.resize(row);
	for (int i = 0; i < row; i++) {
		data[i].resize(column);
	}
}

double& Matrix::value(size_t row, size_t column) {
	assert(this->row > row && "row index out of bound");
	assert(this->column > column && "column index out of bound");
	return data[row][column];
}

Matrix Matrix::minorMatrix(size_t row, size_t column) {
	assert(this->row > row && "row index out of bound");
	assert(this->column > column && "column index out of bound");
	Matrix rtn(data);
	rtn.data.erase(rtn.data.begin() + row);
	for (int i = 0; i < this->row - 1; i++) {
		rtn.data[i].erase(rtn.data[i].begin() + column);
	}
	return rtn;
}

Matrix Matrix::inverseMatrix() {
	assert(row == column && "not a square matrix");
	assert(determinant() != 0 && "determinant is zero");
	Matrix rtn;
	rtn.resize(row, column);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			rtn.data[i][j] = cofactor(i, j);
		}
	}
	rtn.transpose();
	return rtn / determinant();
}

double Matrix::determinant() {
	assert(row == column && "not a square matrix");
	double rtn = 0;
	if (row == 2) {
		rtn = data[0][0] * data[1][1] - data[1][0] * data[0][1];
	}
	else {
		for (int i = 0; i < row; i++) {
			rtn += data[i][0] * cofactor(i, 0);
		}
	}
	return rtn;
}

double Matrix::cofactor(size_t row, size_t column) {
	assert(this->row > row && "row index out of bound");
	assert(this->column > column && "column index out of bound");
	int sign = ((row + column) % 2 == 0) ? 1 : -1;
	return sign * minorMatrix(row, column).determinant();
}

void Matrix::transpose() {
	vec2 temp = data;
	resize(column, row);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			data[i][j] = temp[j][i];
		}
	}
}

void Matrix::handleZero() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (fabs(data[i][j]) < TOL) {
				data[i][j] = 0;
			}
		}
	}
}

void Matrix::show(int minWidth) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			std::cout << std::setw(minWidth) << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}