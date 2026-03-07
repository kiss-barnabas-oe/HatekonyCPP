#include <iostream>
#include <string>
#include "fraction.h"
#include <cmath>

Fraction::Fraction(const int numerator, const int denominator)
{
	if (denominator == 0)
		throw std::invalid_argument("Denominator can't be 0.");

	if (denominator < 0)
		throw std::invalid_argument("Denominator can't be below 0.");

	this->numerator = numerator;
	this->denominator = denominator;
	SimplestForm();
}

Fraction::Fraction(const double number)
{
	double numerator = number;
	int denominator = 1;
	double intPart;

	while (std::modf(numerator, &intPart) != 0.0)
	{
		numerator *= 10;
		denominator *= 10;
	}

	*this = Fraction(static_cast<int>(numerator), denominator);
}

Fraction::~Fraction()
{

}

Fraction& Fraction::SimplestForm()
{
	if (numerator == 0)
		return *this;
	int res = std::min(std::abs(numerator), static_cast<int>(denominator));
	while (res > 1)
	{
		if (numerator % res == 0 && denominator % res == 0)
			break;
		res--;
	}
	if (res > 1)
	{
		std::cout << this->ToString() << " fraction simplified by " << res << std::endl;
		numerator /= res;
		denominator /= res;
	}
	return *this;
}

int Fraction::GetDenominator() const
{
	return this->denominator;
}

int Fraction::GetNumerator() const
{
	return this->numerator;
}

std::string Fraction::ToString() const
{
	if (denominator == 1)
		return std::to_string(numerator);
	std::string s = "";
	s += std::to_string(numerator);
	s += "/";
	s += std::to_string(denominator);
	return s;
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

Fraction operator+(const Fraction& a, const Fraction& b)
{
	const int commonGround = a.GetDenominator() * b.GetDenominator();
	const int tempnum = a.GetNumerator() * commonGround / a.GetDenominator() + b.GetNumerator() * commonGround / b.GetDenominator();
	Fraction temp(tempnum, commonGround);
	temp.SimplestForm();
	return temp;
}

Fraction& Fraction::operator+=(const Fraction& other)
{
	*this = *this + other;
	return *this;
}

Fraction operator-(const Fraction& a, const Fraction& b)
{
	Fraction temp(b);
	temp *= -1;
	return operator+(a, temp);
}

Fraction& Fraction::operator-=(const Fraction& other)
{
	*this = *this - other;
	return *this;
}

Fraction operator*(const Fraction& a, const Fraction& b)
{
	Fraction temp(a.GetNumerator() * b.GetNumerator(), a.GetDenominator() * b.GetDenominator());
	temp.SimplestForm();
	return temp;
}

Fraction& Fraction::operator*=(const Fraction& other)
{
	*this = *this * other;
	return *this;
}

Fraction operator/(const Fraction& a, const Fraction& b)
{
	Fraction temp(b.GetDenominator(), b.GetNumerator());
	return operator*(a, temp);
}

Fraction& Fraction::operator/=(const Fraction& other)
{
	*this = *this / other;
	return *this;
}

bool Fraction::operator!=(const Fraction& other)
{
	return !(*this == other);
}

bool Fraction::operator==(const Fraction& other)
{
	if (this->numerator == other.GetNumerator() && this->denominator == other.GetDenominator())
		return true;
	return false;
}

bool Fraction::operator<(const Fraction& other)
{
	const int commonGround = this->denominator * other.GetDenominator();
	const int tempnuma = this->numerator * commonGround / this->denominator;
	const int tempnumb = other.GetNumerator() * commonGround / other.GetDenominator();
	if (tempnuma < tempnumb)
		return true;
	return false;
}

bool Fraction::operator>(const Fraction& other)
{
	Fraction temp = other;
	return temp < *this;
}

bool Fraction::operator<=(const Fraction& other)
{
	if (*this == other)
		return true;
	else
		return *this < other;
}

bool Fraction::operator>=(const Fraction& other)
{
	Fraction temp = other;
	return temp <= *this;
}

std::ostream& operator<<(std::ostream& os, const Fraction& other)
{
	os << other.ToString();
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& other)
{
	is >> other.numerator;
	is >> other.denominator;
	return is;
}