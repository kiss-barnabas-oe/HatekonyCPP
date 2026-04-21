#include <iostream>
#include <string>
#include "fraction.h"
#include <cmath>
#include <numeric>
#include <sstream>

Fraction::Fraction(const int numerator, const int denominator)
	: numerator(numerator)
	, denominator(denominator)
{
	if (denominator == 0)
		throw std::invalid_argument("Denominator can't be 0.");

	if (denominator < 0)
	{
		this->numerator *= -1;
		this->denominator *= -1;
	}		
	
	SimplestForm();
}

Fraction::Fraction(const double number)
	: numerator(static_cast<int>(std::round(number * scale)))
	, denominator(scale)
{	
	SimplestForm();
}

Fraction& Fraction::SimplestForm()
{
	if (numerator == 0)
		return *this;
	const int res = std::gcd(numerator, denominator);
	if (res > 1)
	{		
		numerator /= res;
		denominator /= res;
	}
	return *this;
}

Fraction Fraction::operator-() const
{
	return Fraction(-numerator, denominator);
}

Fraction Fraction::operator+(const Fraction& other) const
{	
	Fraction temp(*this);
	temp += other;
	return temp;
}

Fraction& Fraction::operator+=(const Fraction& other)
{	
	numerator = numerator * other.denominator + other.numerator * denominator;
	denominator *= other.denominator;
	SimplestForm();
	return *this;
}

Fraction Fraction::operator-(const Fraction& other) const
{
	Fraction temp(*this);
	temp -= other;
	return temp;
}

Fraction& Fraction::operator-=(const Fraction& other)
{	
	return *this += -other;
}

Fraction Fraction::operator*(const Fraction& other) const
{
	Fraction temp(*this);
	temp *= other;
	return temp;
}

Fraction& Fraction::operator*=(const Fraction& other)
{
	numerator *= other.numerator;
	denominator *= other.denominator;
	SimplestForm();
	return *this;
}

Fraction Fraction::operator/(const Fraction& other) const
{
	Fraction temp(*this);
	temp /= other;
	return temp;	
}

Fraction& Fraction::operator/=(const Fraction& other)
{
	if (other.numerator == 0)
		throw std::invalid_argument("Division by zero");
	numerator *= other.denominator;
	denominator *= other.numerator;
	SimplestForm();
	return *this;
}

Fraction operator+(int number, const Fraction& other)
{
	return other + number;
}

Fraction operator-(int number, const Fraction& other)
{
	return -other + number;
}

Fraction operator*(int number, const Fraction& other)
{
	return other * number;
}

Fraction operator/(int number, const Fraction& other)
{
	return Fraction(number) / other;
}

bool Fraction::operator!=(const Fraction& other) const
{
	return !(*this == other);
}

bool Fraction::operator==(const Fraction& other) const
{
	return (this->numerator == other.numerator && this->denominator == other.denominator);
}

bool Fraction::operator<(const Fraction& other) const
{
	return static_cast<double>(*this) < static_cast<double>(other);	
}

bool Fraction::operator>(const Fraction& other) const
{	
	return other < *this;
}

bool Fraction::operator<=(const Fraction& other) const
{
	return *this == other || *this < other;
}

bool Fraction::operator>=(const Fraction& other) const
{	
	return other <= *this;
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
	return numerator != 0;
}

Fraction::operator std::string() const {
	if (denominator == 1)
		return std::to_string(numerator);
	return std::to_string(numerator) + "/" + std::to_string(denominator);
}

std::ostream& operator<<(std::ostream& os, const Fraction& other)
{
	return os << static_cast<std::string>(other);	
}

std::istream& operator>>(std::istream& is, Fraction& other)
{
	std::string s;
	std::getline(is, s);

	if (!is) return is;

	try
	{
		if (s.find('/') != std::string::npos)
		{
			size_t pos = s.find('/');
			int n = std::stoi(s.substr(0, pos));
			int d = std::stoi(s.substr(pos + 1));
			other = Fraction(n, d);
		}
		else if (s.find('.') != std::string::npos)
		{
			double val = std::stod(s);
			other = Fraction(static_cast<int>(val * Fraction::scale), Fraction::scale);
		}
		else
		{
			other = Fraction(std::stoi(s), 1);
		}
	}
	catch (...)
	{
		is.setstate(std::ios::failbit);
	}

	return is;
}

Fraction Fraction::Parse(const std::string& input)
{
	std::istringstream iss(input);
	Fraction f(0, 1);

	if (!(iss >> f))
		throw std::invalid_argument("Invalid fraction format");

	return f;
}
