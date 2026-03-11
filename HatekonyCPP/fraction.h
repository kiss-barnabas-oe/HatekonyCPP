#pragma once

class Fraction {
public:
	Fraction(const int numerator, const int denominator = 1);
	Fraction(const double number);
	Fraction& SimplestForm();
	
	Fraction operator+(const int number);
	Fraction operator-(const int number);
	Fraction operator*(const int number);
	Fraction operator/(const int number);

	Fraction& operator+=(const int number);
	Fraction& operator-=(const int number);
	Fraction& operator*=(const int number);
	Fraction& operator/=(const int number);

	Fraction& operator+=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);

	Fraction operator+(const Fraction& other);
	Fraction operator-(const Fraction& other);
	Fraction operator*(const Fraction& other);
	Fraction operator/(const Fraction& other);

	bool operator==(const Fraction& other) const;
	bool operator!=(const Fraction& other) const;
	bool operator<(const Fraction& other) const;
	bool operator>(const Fraction& other) const;
	bool operator<=(const Fraction& other) const;
	bool operator>=(const Fraction& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Fraction& other);

	friend std::istream& operator>>(std::istream& is, Fraction& other);

	explicit operator int() const
	{
		return numerator / static_cast<int>(denominator);
	}

	explicit operator double() const
	{
		return static_cast<double>(numerator) / static_cast<double>(denominator);
	}

	explicit operator bool() const
	{
		return numerator > 0;
	}

private:
	int numerator;
	unsigned int denominator;
};