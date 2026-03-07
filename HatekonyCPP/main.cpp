#include <iostream>
#include "fraction.h"

int main()
{
    // Negative denominator exception
    try {
        Fraction negativedenominator(1, -1);
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    // Zero denominator exception
    try {
        Fraction zerodenominator(1, 0);
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    // Negative denominator exception
    Fraction f10(10, 20);
    std::cout << f10.ToString() << std::endl;
    Fraction f1(2);
    std::cout << f1.ToString() << std::endl;
    Fraction f2(1, 5);
    std::cout << f2.ToString() << std::endl;
    Fraction f3(3.14);
    std::cout << f3.ToString() << std::endl;
    Fraction f_overflow(300.14);
    std::cout << f_overflow.ToString() << std::endl;
    Fraction f4(f10);
    std::cout << f4.ToString() << std::endl;

    std::cout << "operators:" << std::endl;
    Fraction f21 = f2 + 2;
    std::cout << "1/5 + 2 = " << f21.ToString() << std::endl;
    f21 = f21 - 2;
    std::cout << "11/5 - 2 = " << f21.ToString() << std::endl;
    f21 -= 2;
    std::cout << "1/5 -= 2 = " << f21.ToString() << std::endl;
    f21 += 2;
    std::cout << "-9/5 += 2 = " << f21.ToString() << std::endl;

    Fraction f31 = f21 + f2;
    std::cout << "1/5 + 1/5 = " << f31.ToString() << std::endl;
    f31 = f31 - f2;
    std::cout << "2/5 - 1/5 = " << f31.ToString() << std::endl;

    f31 += f2;
    std::cout << "1/5 += 1/5 = " << f31.ToString() << std::endl;
    f31 -= f2;
    std::cout << "2/5 -= 1/5 = " << f31.ToString() << std::endl;
    f31 += 2;
    std::cout << "1/5 += 2 = " << f31.ToString() << std::endl;
    f31 -= 2;
    std::cout << "11/5 -= 2 = " << f31.ToString() << std::endl;

    f2 = f2 * 10;
    std::cout << "1/5 * 10 = " << f2.ToString() << std::endl;
    f2 = f2 / 10;
    std::cout << "2 / 10 = " << f2.ToString() << std::endl;
    f2 *= 10;
    std::cout << "1/5 *= 10 = " << f2.ToString() << std::endl;
    f2 /= 10;
    std::cout << "2 /= 10 = " << f2.ToString() << std::endl;

    f2 = f2 * f2;
    std::cout << "1/5 * 1/5 = " << f2.ToString() << std::endl;
    f2 = f2 / Fraction(1, 5);
    std::cout << "1/25 / 1/5 = " << f2.ToString() << std::endl;

    f2 *= f2;
    std::cout << "1/5 *= 1/5 = " << f2.ToString() << std::endl;
    f2 /= Fraction(1, 5);
    std::cout << "1/25 /= 1/5 = " << f2.ToString() << std::endl;

    Fraction equal(1, 5);
    Fraction smaller(1, 10);
    Fraction larger(1, 2);
    if (f2 == equal)
    {
        std::cout << "1/5 is equal to 1/5" << std::endl;
    }

    if (f2 < larger)
    {
        std::cout << "1/5 is smaller than 1/2" << std::endl;
    }

    if (f2 > smaller)
    {
        std::cout << "1/5 is larger than 1/10" << std::endl;
    }

    /*Fraction consolein(1, 1);
    std::cin >> consolein;

    std::cout << consolein;*/
}
