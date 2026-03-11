#include <iostream>
#include <string>
#include "fraction.h"
#include <cmath>
#include <numeric>

Fraction::Fraction(const int numerator, const int denominator)
	: numerator(numerator)
	, denominator(denominator)
{
	if (denominator == 0)
		throw std::invalid_argument("Denominator can't be 0.");

	if (denominator < 0)
		throw std::invalid_argument("Denominator can't be below 0.");
	
	SimplestForm();
}

Fraction::Fraction(const double number)
	: numerator(std::round(number * 1000000))
	, denominator(1000000)
{	
	SimplestForm();
}

Fraction& Fraction::SimplestForm()
{
	if (numerator == 0)
		return *this;
	int res = std::gcd(numerator, denominator);
	if (res > 1)
	{
		std::cout << *this << " fraction simplified by " << res << std::endl;
		numerator /= res;
		denominator /= res;
	}
	return *this;
}

Fraction Fraction::operator+(const int number)
{
	Fraction temp(this->numerator + number * denominator, denominator);
	temp.SimplestForm();
	return temp;
}

Fraction& Fraction::operator+=(const int number)
{
	*this = *this + number;
	return *this;
}

Fraction Fraction::operator-(const int number)
{
	int minus = number * -1;
	return operator+(minus);
}

Fraction& Fraction::operator-=(const int number)
{
	*this = *this - number;
	return *this;
}

Fraction Fraction::operator*(const int number)
{
	Fraction temp(number * numerator, denominator);
	temp.SimplestForm();
	return temp;
}

Fraction& Fraction::operator*=(const int number)
{
	*this = *this * number;
	SimplestForm();
	return *this;
}

Fraction Fraction::operator/(const int number)
{
	Fraction temp(this->numerator, this->denominator * number);
	temp.SimplestForm();
	return temp;
}

Fraction& Fraction::operator/=(const int number)
{
	*this = *this / number;
	SimplestForm();
	return *this;
}

Fraction Fraction::operator+(const Fraction& other)
{
	const int commonGround = this->denominator * other.denominator;
	const int tempnum = this->numerator * commonGround / this->denominator + other.numerator * commonGround / other.denominator;
	Fraction temp(tempnum, commonGround);
	temp.SimplestForm();
	return temp;
}

Fraction& Fraction::operator+=(const Fraction& other)
{
	*this = *this + other;
	return *this;
}

Fraction Fraction::operator-(const Fraction& other)
{
	Fraction temp(other);
	temp *= -1;
	return operator+(temp);
}

Fraction& Fraction::operator-=(const Fraction& other)
{
	*this = *this - other;
	return *this;
}

Fraction Fraction::operator*(const Fraction& other)
{
	Fraction temp(this->numerator * other.numerator, this->denominator * other.denominator);
	temp.SimplestForm();
	return temp;
}

Fraction& Fraction::operator*=(const Fraction& other)
{
	*this = *this * other;
	return *this;
}

Fraction Fraction::operator/(const Fraction& other)
{
	Fraction temp(other.denominator, other.numerator);
	return operator*(temp);
}

Fraction& Fraction::operator/=(const Fraction& other)
{
	*this = *this / other;
	return *this;
}

bool Fraction::operator!=(const Fraction& other) const
{
	return !(*this == other);
}

bool Fraction::operator==(const Fraction& other) const
{
	if (this->numerator == other.numerator && this->denominator == other.denominator)
		return true;
	return false;
}

bool Fraction::operator<(const Fraction& other) const
{
	const int commonGround = this->denominator * other.denominator;
	const int tempnuma = this->numerator * commonGround / this->denominator;
	const int tempnumb = other.numerator * commonGround / other.denominator;
	if (tempnuma < tempnumb)
		return true;
	return false;
}

bool Fraction::operator>(const Fraction& other) const
{
	Fraction temp = other;
	return temp < *this;
}

bool Fraction::operator<=(const Fraction& other) const
{
	if (*this == other)
		return true;
	else
		return *this < other;
}

bool Fraction::operator>=(const Fraction& other) const
{
	Fraction temp = other;
	return temp <= *this;
}

Fraction::operator int() const
{
	return numerator / static_cast<int>(denominator);	
}

Fraction::operator double() const
{
	return static_cast<double>(numerator) / static_cast<double>(denominator);
}

Fraction::operator bool() const
{
	return numerator > 0;
}

std::ostream& operator<<(std::ostream& os, const Fraction& other)
{
	if (other.denominator == 1)
		os << std::to_string(other.numerator);	
	else
		os << std::to_string(other.numerator) << "/" << std::to_string(other.denominator);
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& other)
{
	std::string s;
	is >> s;

	if (s.find('.') != std::string::npos)
	{
		other = Fraction(std::stod(s));
	}
	else if (s.find('/') != std::string::npos)
	{
		int num = std::stoi(s.substr(0, s.find('/')));
		int den = std::stoi(s.substr(s.find('/') + 1));
		other = Fraction(num, den);
	}
	else
	{
		int num = std::stoi(s);
		int den;

		if (is >> den)
			other = Fraction(num, den);
		else
			other = Fraction(num, 1);
	}

	return is;
}