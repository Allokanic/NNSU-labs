#pragma once

#include <iostream>
#include <string>

class Rational {
public:
	Rational();
	Rational(const int value);
	Rational(const Rational& other);
	Rational(const std::string format);
	~Rational() = default;

	Rational operator =(const Rational& other);
	Rational operator =(const int& other);

	Rational& operator += (const Rational& other);
	Rational& operator += (const int& other);
	Rational& operator -= (const Rational& other);
	Rational& operator -= (const int& other);
	Rational& operator *= (const Rational& other);
	Rational& operator *= (const int& other);
	Rational& operator /= (const Rational& other);
	Rational& operator /= (const int& other);

	Rational operator +(const int other);
	Rational operator -(const int other);
	Rational operator *(const int other);
	Rational operator /(const int other);
	Rational operator +(const Rational& other);
	Rational operator -(const Rational& other);
	Rational operator *(const Rational& other);
	Rational operator /(const Rational& other);

	bool operator == (const Rational& other);
	bool operator != (const Rational& other);
	bool operator <(const Rational& other);
	bool operator >(const Rational& other);

	friend std::ostream& operator << (std::ostream& stream, const Rational& object);

private:
	int num;
	size_t den;

	void shorten();
};