#pragma once

class Fraction {
public:
	Fraction(const int numerator, const int denominator = 1);
	Fraction(const double number);
	Fraction& SimplestForm();

	Fraction operator-() const;

	Fraction& operator+=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);

	Fraction operator+(const Fraction& other) const;
	Fraction operator-(const Fraction& other) const;
	Fraction operator*(const Fraction& other) const;
	Fraction operator/(const Fraction& other) const;

	bool operator==(const Fraction& other) const;
	bool operator!=(const Fraction& other) const;
	bool operator<(const Fraction& other) const;
	bool operator>(const Fraction& other) const;
	bool operator<=(const Fraction& other) const;
	bool operator>=(const Fraction& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Fraction& other);

	friend std::istream& operator>>(std::istream& is, Fraction& other);

	explicit operator int() const;	

	explicit operator double() const;

	explicit operator bool() const;

	static Fraction Parse(const std::string& input);

private:
	int numerator;
	unsigned int denominator;
};