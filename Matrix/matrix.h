#pragma once 

#include <iostream>
#include <vector>
#include "rational.h"

class Matrix {
public:
	Matrix();
	Matrix(int _len, int _wid);
	Matrix(const std::vector <std::vector <Rational>>& _data);
	~Matrix() = default;

	Matrix operator =(const Matrix& other);
	std::vector<Rational>& operator [](int pos);
	
	Matrix& operator +=(const Matrix& other);
	Matrix& operator -=(const Matrix& other);
	Matrix& operator *=(const Matrix& other);
	Matrix& operator *=(const int other);

	Matrix operator +(const Matrix& other);
	Matrix operator -(const Matrix& other);
	Matrix operator *(const Matrix& other);
	Matrix operator *(const int other);

	bool operator ==(const Matrix& other);
	bool operator !=(const Matrix& other);

	Rational get_determinant();
	void transope();
	Matrix get_inverse_matrix();
	void print();
	void read();

private:
	void substrack_lines(const int reduced_index, const int deductible_index);
	void divide_line(const int index, const Rational& divider);
	void multiplicate_line(const int index, const Rational& multiplier);
	bool check_for_summarising(const Matrix& object);
	bool check_for_multiplicating(const Matrix& object);

	std::vector <std::vector <Rational>> data;
	size_t len, wid;
};
