#include "matrix.h"

Matrix::Matrix() {
	height = width = 0;
}

Matrix::Matrix(int _len, int _width) : height(_len), width(_width) {
	data.resize(_len);
	for (int i = 0; i < _len; ++i)
		data[i].resize(_width);
}

Matrix::Matrix(const std::vector <std::vector <Rational>>& _data) {
	data = _data;
	height = data.size();
	width = (height ? data[0].size() : 0);
}

Matrix Matrix::operator =(const Matrix& other) {
	height = other.height;
	width = other.width;
	data = other.data;
	return *this;
}
std::vector<Rational>& Matrix::operator [](int pos) {
	return data[pos];
}

Matrix& Matrix::operator +=(const Matrix& other) {
	if (height == other.height && width == other.width) {
		for (int i = 0; i < height; ++i) 
			for (int j = 0; j < width; ++j) 
				data[i][j] += other.data[i][j];
		return *this;
	}
	else {
		std::cout << "Error: operation +\nMatrixes have wrong parameters for this operation";
	}
}

Matrix& Matrix::operator -=(const Matrix& other) {
	if (height == other.height && width == other.width) {
		for (int i = 0; i < height; ++i) 
			for (int j = 0; j < width; ++j) 
				data[i][j] -= other.data[i][j];
		return *this;
	}
	else {
		std::cout << "Error: operation -\nMatrixes have wrong parameters for this operation";
	}
}

Matrix& Matrix::operator *=(const Matrix& other) {
	if (width == other.height) {
		Matrix new_object(width, other.height);
		for (int i = 0; i < height; ++i) 
			for (int j = 0; j < other.width; ++j) 
				for (int k = 0; k < width; ++k) 
					new_object[i][j] += data[i][k] * other.data[k][j];
		data = new_object.data;
		width = other.width;
		return *this;
	}
	else {
		std::cout << "Error: operation *\nMatrixes have wrong parameters for this operation";
	}
}

Matrix& Matrix::operator *=(const int multiplier) {
	for (int i = 0; i < height; ++i) 
		for (int j = 0; j < width; ++j) 
			data[i][j] *= multiplier;
	return *this;
}

Matrix Matrix::operator +(const Matrix& other) {
	Matrix new_object(*this);
	return new_object += other;
}

Matrix Matrix::operator -(const Matrix& other) {
	Matrix new_object(*this);
	return new_object -= other;
}

Matrix Matrix::operator *(const Matrix& other) {
	Matrix new_object(*this);
	return new_object *= other;
}

Matrix Matrix::operator *(const int multiplier) {
	Matrix new_object(*this);
	return new_object *= multiplier;
}

bool Matrix::operator ==(const Matrix& other) {
	if (data.size() == other.data.size()) {
		for (int i = 0; i < height; ++i) 
			for (int j = 0; j < width; ++j) 
				if (data[i][j] != other.data[i][j])
					return false;
		return true;
	}
	return false;
}
bool Matrix::operator !=(const Matrix& other) {
	return !(*this == other);
}

Rational Matrix::get_determinant() {
	if (height != width) return 0;

	Matrix new_object(*this);
	std::vector<Rational> multiples;
	Rational cur_divider;

	for (int i = 0; i < width; ++i) { //stolb
		for (int j = i; j < height; ++j) { //line
			cur_divider = new_object.data[j][i];
			if (cur_divider != 0) 
				new_object.divide_line(j, cur_divider);
			if (cur_divider != 0 || i == height-1)
				multiples.push_back(cur_divider);
		}
		for (int j = i + 1; j < height; ++j) {
			if (new_object.data[j][i] != 0)
				new_object.substract_lines(j, i);
		}
	}
	Rational res = 1;
	for (int i = 0; i < multiples.size(); ++i) 
		res *= multiples[i];
	return res;
}

void Matrix::transpose() {
	data.resize(std::max(height, width));
	for (int i = 0; i < std::max(height,width); ++i) 
		data[i].resize(std::max(height, width));
	for (int i = 0; i < std::max(height, width); ++i) 
		for (int j = i; j < std::max(height, width); ++j) 
			std::swap(data[i][j], data[j][i]);
	data.resize(width);
	for (int i = 0; i < width; ++i) 
		data[i].resize(height);
	std::swap(height, width);
}

Matrix Matrix::get_transposed_matrix() {
	Matrix result(*this);
	result.data.resize(std::max(height, width));
	for (int i = 0; i < std::max(height, width); ++i)
		result.data[i].resize(std::max(height, width));
	for (int i = 0; i < std::max(height, width); ++i)
		for (int j = i; j < std::max(height, width); ++j)
			std::swap(result.data[i][j], result.data[j][i]);
	result.data.resize(width);
	for (int i = 0; i < width; ++i)
		result.data[i].resize(height);
	std::swap(result.height, result.width);
	return result;
}

Matrix Matrix::get_inverse_matrix() {
	if (get_determinant() == 0) {
		std::cout << "there is no inversed matrix\n";
		return data;
	}
	Matrix copy(*this);
	Matrix result(*this);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			result[i][j] = 0;
			if (i == j) 
				result[i][j] = 1;
		}
	}
	Rational cur_divider;
	for (int i = 0; i < height; ++i) { //column
		for (int j = i; j < height; ++j) { //line
			cur_divider = copy[j][i];
			if (cur_divider != 0) {
				copy.divide_line(j, cur_divider);
				result.divide_line(j, cur_divider);
			}
		}
		for (int j = i + 1; j < height; ++j) {
			if (copy[j][i] != 0) {
				copy.substract_lines(j, i);
				result.substract_lines(j, i);
			}
		}
	}
	for (int i = height - 1; i > 0; --i) { //column
		for (int j = i - 1; j > -1; --j) { //line
			Rational tmp = copy[j][i];
			copy.multiplicate_line(i, tmp);
			result.multiplicate_line(i, tmp);
			copy.substract_lines(j, i);
			result.substract_lines(j, i);
			copy.divide_line(i, tmp);
			result.divide_line(i, tmp);
		}
	}
	return result;
}

void Matrix::inverse() {
	if (get_determinant() == 0) {
		std::cout << "there is no inversed matrix\n";
		return;
	}
	Matrix result(*this);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height; ++j) {
			result[i][j] = 0;
			if (i == j)
				result[i][j] = 1;
		}
	}
	Rational cur_divider;
	for (int i = 0; i < height; ++i) { //column
		for (int j = i; j < height; ++j) { //line
			cur_divider = data[j][i];
			if (cur_divider != 0) {
				divide_line(j, cur_divider);
				result.divide_line(j, cur_divider);
			}
		}
		for (int j = i + 1; j < height; ++j) {
			if (data[j][i] != 0) {
				substract_lines(j, i);
				result.substract_lines(j, i);
			}
		}
	}
	for (int i = height - 1; i > 0; --i) { //column
		for (int j = i - 1; j > -1; --j) { //line
			Rational tmp = data[j][i];
			multiplicate_line(i, tmp);
			result.multiplicate_line(i, tmp);
			substract_lines(j, i);
			result.substract_lines(j, i);
			divide_line(i, tmp);
			result.divide_line(i, tmp);
		}
	}
	data = result.data;
	return;
}

void Matrix::print() {
	for (int i = 0; i < height; ++i) {
		std::cout << '(';
		for (int j = 0; j < width; ++j) {
			std::cout << data[i][j];
			if (j == width - 1)
				std::cout << ")\n";
			else
				std::cout << '\t';
		}
	}
}

void Matrix::read() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int tmp;
			std::cin >> tmp;
			data[i][j] = tmp;
		}
	}
}

void Matrix::divide_line(const int index, const Rational& divider) {
	for (int i = 0; i < width; ++i) 
		data[index][i] /= divider;
}

void Matrix::substract_lines(int reduced_index, int deductible_index) {
	for (int i = 0; i < width; ++i) 
		data[reduced_index][i] -= data[deductible_index][i];
}

void Matrix::multiplicate_line(const int index,const Rational& multiplier) {
	for (int i = 0; i < width; ++i) 
		data[index][i] *= multiplier;
}
