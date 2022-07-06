#include "matrix.h"

Matrix::Matrix() {
	len = wid = 0;
}

Matrix::Matrix(int _len, int _wid) : len(_len), wid(_wid) {
	data.resize(_len);
	for (int i = 0; i < _len; ++i)
		data[i].resize(_wid);
}

Matrix::Matrix(const std::vector <std::vector <Rational>>& _data) {
	data = _data;
	len = data.size();
	wid = (len ? data[0].size() : 0);
}

Matrix Matrix::operator =(const Matrix& other) {
	len = other.len;
	wid = other.wid;
	data = other.data;
	return *this;
}
std::vector<Rational>& Matrix::operator [](int pos) {
	return data[pos];
}

Matrix& Matrix::operator +=(const Matrix& other) {
	if (len == other.len && wid == other.wid) {
		for (int i = 0; i < len; ++i) 
			for (int j = 0; j < wid; ++j) 
				data[i][j] += other.data[i][j];
		return *this;
	}
	else
		std::cout << "Error: operation +\nMatrixes have wrong parameters for this operation";
	
}

Matrix& Matrix::operator -=(const Matrix& other) {
	if (len == other.len && wid == other.wid) {
		for (int i = 0; i < len; ++i) 
			for (int j = 0; j < wid; ++j) 
				data[i][j] -= other.data[i][j];
		return *this;
	}
	else 
		std::cout << "Error: operation -\nMatrixes have wrong parameters for this operation";
}

Matrix& Matrix::operator *=(const Matrix& other) {
	if (wid == other.len) {
		Matrix new_object(wid, other.len);
		for (int i = 0; i < len; ++i) 
			for (int j = 0; j < other.wid; ++j) 
				for (int k = 0; k < wid; ++k) 
					new_object[i][j] += data[i][k] * other.data[k][j];
		data = new_object.data;
		wid = other.wid;
		return *this;
	}
	else
		std::cout << "Error: operation *\nMatrixes have wrong parameters for this operation";
}

Matrix& Matrix::operator *=(const int other) {
	for (int i = 0; i < len; ++i) 
		for (int j = 0; j < wid; ++j) 
			data[i][j] *= other;
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

Matrix Matrix::operator *(const int other) {
	Matrix new_object(*this);
	return new_object *= other;
}

bool Matrix::operator ==(const Matrix& other) {
	if (data.size() == other.data.size()) {
		for (int i = 0; i < len; ++i) 
			for (int j = 0; j < wid; ++j) 
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
	if (len != wid) return 0;

	Matrix new_object(*this);
	std::vector<Rational> multiples;
	Rational cur_divider;

	for (int i = 0; i < wid; ++i) { //stolb
		for (int j = i; j < len; ++j) { //line
			cur_divider = new_object.data[j][i];
			if (cur_divider != 0) 
				new_object.divide_line(j, cur_divider);
			if (cur_divider != 0 || i == len-1)
				multiples.push_back(cur_divider);
		}
		for (int j = i + 1; j < len; ++j) {
			if (new_object.data[j][i] != 0)
				new_object.substrack_lines(j, i);
		}
	}
	Rational res = 1;
	for (int i = 0; i < multiples.size(); ++i) 
		res *= multiples[i];
	return res;
}

void Matrix::transope() {
	data.resize(std::max(len, wid));
	for (int i = 0; i < std::max(len,wid); ++i) 
		data[i].resize(std::max(len, wid));
	for (int i = 0; i < std::max(len, wid); ++i) 
		for (int j = i; j < std::max(len, wid); ++j) 
			std::swap(data[i][j], data[j][i]);
	data.resize(wid);
	for (int i = 0; i < wid; ++i) 
		data[i].resize(len);
	std::swap(len, wid);
}

Matrix Matrix::get_inverse_matrix() {
	if (get_determinant() == 0) {
		std::cout << "there is no inversed matrix\n";
		return data;
	}
	Matrix copy(*this);
	Matrix result(*this);
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			result[i][j] = 0;
			if (i == j) 
				result[i][j] = 1;
		}
	}
	Rational cur_divider;
	for (int i = 0; i < len; ++i) { //column
		for (int j = i; j < len; ++j) { //line
			cur_divider = copy[j][i];
			if (cur_divider != 0) {
				copy.divide_line(j, cur_divider);
				result.divide_line(j, cur_divider);
			}
		}
		for (int j = i + 1; j < len; ++j) {
			if (copy[j][i] != 0) {
				copy.substrack_lines(j, i);
				result.substrack_lines(j, i);
			}
		}
	}
	for (int i = len - 1; i > 0; --i) { //column
		for (int j = i - 1; j > -1; --j) { //line
			Rational tmp = copy[j][i];
			copy.multiplicate_line(i, tmp);
			result.multiplicate_line(i, tmp);
			copy.substrack_lines(j, i);
			result.substrack_lines(j, i);
			copy.divide_line(i, tmp);
			result.divide_line(i, tmp);
		}
	}
	return result;
}

void Matrix::print() {
	for (int i = 0; i < len; ++i) {
		std::cout << '(';
		for (int j = 0; j < wid; ++j) {
			std::cout << data[i][j];
			if (j == wid - 1)
				std::cout << ")\n";
			else
				std::cout << '\t';
		}
	}
}

void Matrix::read() {
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < wid; ++j) {
			int tmp;
			std::cin >> tmp;
			data[i][j] = tmp;
		}
	}
}

void Matrix::divide_line(const int index, const Rational& divider) {
	for (int i = 0; i < wid; ++i) 
		data[index][i] /= divider;
}

void Matrix::substrack_lines(int reduced_index, int deductible_index) {
	for (int i = 0; i < wid; ++i) 
		data[reduced_index][i] -= data[deductible_index][i];
}

void Matrix::multiplicate_line(const int index,const Rational& multiplier) {
	for (int i = 0; i < wid; ++i) 
		data[index][i] *= multiplier;
}
