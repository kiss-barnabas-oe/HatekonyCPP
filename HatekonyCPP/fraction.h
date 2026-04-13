#pragma once

class Fraction {
public:
	Fraction(const int numerator, const int denominator = 1);
	Fraction(const double number);

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

	explicit operator std::string() const;

	static Fraction Parse(const std::string& input);

private:
	int numerator;
	unsigned int denominator;

	constexpr static int scale = 1000000;

 Fraction& SimplestForm();
};

Fraction operator+(int number, const Fraction& other);
Fraction operator-(int number, const Fraction& other);
Fraction operator*(int number, const Fraction& other);
Fraction operator/(int number, const Fraction& other);