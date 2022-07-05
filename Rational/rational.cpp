#include "rational.h"

long long gcd(long long a, long long c) {
	long long t;
	while (c != 0) {
		t = c;
		c = a % c;
		a = t;
	}
	return a;
}

long long lcm(long long a, long long c) {
	return (a * c) / gcd(a, c);
}

Rational::Rational() {
	num = 0;
	den = 1;
}

Rational::Rational(const int value) {
	num = value;
	den = 1;
}

Rational::Rational(const Rational& other) {
	num = other.num;
	den = other.den;
}

Rational::Rational(const std::string format) {
	int i = 0;
	std::string numen, denumer;
	while (format[i] != '/') 
		numen.push_back(format[i++]);
	i++;
	while (i < format.size()) 
		denumer.push_back(format[i++]);
	std::reverse(numen.begin(), numen.end());
	std::reverse(denumer.begin(), denumer.end());
	num = atoi(numen.c_str());
	den = atoi(denumer.c_str());
	if (!den) den = 1;
}

Rational Rational::operator =(const Rational& other) {
	this->num = other.num;
	this->den = other.den;
	return *this;
}

Rational& Rational::operator += (const Rational& other) {
	int common_den = lcm(den, other.den);
	num *= (common_den / den);
	num += (other.num * (common_den / other.den));
	shorten();
	return *this;
}
Rational& Rational::operator += (const int& other) {
	num += other * den;
	shorten();
	return *this;
}
Rational& Rational::operator -= (const Rational& other) {
	int common_den = lcm(den, other.den);
	num *= (common_den / den);
	num -= (other.num * (common_den / other.den));
	shorten();
	return *this;
}
Rational& Rational::operator -= (const int& other) {
	num -= other * den;
	shorten();
	return *this;
}
Rational& Rational::operator *= (const Rational& other) {
	num *= other.num;
	den *= other.den;
	shorten();
	return *this;
}
Rational& Rational::operator *= (const int& other) {
	num *= other;
	shorten();
	return *this;
}
Rational& Rational::operator /= (const Rational& other) {
	if (other.num < 0)
		num = -num;
	num = static_cast<int>(num * other.den);
	den = static_cast<size_t>(den * abs(other.num));
	shorten();
	return *this;
}
Rational& Rational::operator /= (const int& other) {
	if (other < 0) 
		num = -num;
	den = static_cast<size_t>(den * abs(other));
	shorten();
	return *this;
}

Rational Rational::operator +(const int other) {
	Rational new_object(*this);
	return new_object += other;
}
Rational Rational::operator -(const int other) {
	Rational new_object(*this);
	return new_object -= other;
}
Rational Rational::operator *(const int other) {
	Rational new_object(*this);
	return new_object *= other;
}
Rational Rational::operator /(const int other) {
	Rational new_object(*this);
	return new_object /= other;
}
Rational Rational::operator +(const Rational& other) {
	Rational new_object(*this);
	return new_object += other;
}
Rational Rational::operator -(const Rational& other) {
	Rational new_object(*this);
	return new_object -= other;
}
Rational Rational::operator *(const Rational& other) {
	Rational new_object(*this);
	return new_object *= other;
}
Rational Rational::operator /(const Rational& other) {
	Rational new_object(*this);
	return new_object /= other;
}

bool Rational::operator == (const Rational& other) {
	return den == other.den && num == other.num;
}
bool Rational::operator != (const Rational& other) {
	return !(*this == other);
}
bool Rational::operator <(const Rational& other) {
	int common_den = lcm(den, other.den);
	return (num * common_den / den) < (other.num * common_den / other.den);
}
bool Rational::operator >(const Rational& other) {
	return (*this != other) && !(*this < other);
}

std::ostream& operator << (std::ostream& stream, const Rational& object) {
	stream << object.num;
	if (object.den != 1)
		stream << '/' << object.den;
	return stream;
}

void Rational::shorten() {
	if (!num) den = 1;
	else {
		size_t tmp = num;
		size_t divider = gcd(tmp, den);
		num /= divider;
		den /= divider;
	}
}