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

Fraction Fraction::operator-() const
{
	return Fraction(-numerator, denominator);
}

Fraction::Fraction(const double number)
	: numerator(static_cast<int>(std::round(number * 1000000)))
	, denominator(1000000)
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
		std::cout << *this << " fraction simplified by " << res << std::endl;
		numerator /= res;
		denominator /= res;
	}
	return *this;
}

Fraction Fraction::operator+(const Fraction& other) const
{	
	Fraction temp(*this);
	temp += other;
	return temp;
}

Fraction& Fraction::operator+=(const Fraction& other)
{
	const int commonGround = denominator * other.denominator;
	numerator = numerator * other.denominator + other.numerator * denominator;
	denominator = commonGround;
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
	Fraction temp(other);
	temp *= -1;
	return *this += temp;
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
	Fraction temp = other;
	return temp < *this;
}

bool Fraction::operator<=(const Fraction& other) const
{
	return *this == other || *this < other;
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
	int num = 1;
	int den = 1;

	if (s.find('.') != std::string::npos)
	{
		other = Fraction(std::stod(s));
	}
	else if (s.find('/') != std::string::npos)
	{
		num = std::stoi(s.substr(0, s.find('/')));
		den = std::stoi(s.substr(s.find('/') + 1));		
	}
	else
	{
		num = std::stoi(s);		

		if (!(is >> den))
			den = 1;
	}
	other = Fraction(num, den);
	return is;
}

Fraction Fraction::Parse(const std::string& input)
{
	std::istringstream iss{ input };
	int numerator;
	int denominator;
	char slash;
	iss >> numerator >> slash >> denominator;
	if (iss.fail() || slash != '/')
		throw std::invalid_argument(input + " was not suitable.");
	return Fraction(numerator, denominator);
}
