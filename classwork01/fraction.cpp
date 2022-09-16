#include <stdio.h>
#include <cmath>
#include <iostream>

class Fraction {
public:
    Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {};

    void printFraction() {  // Выводит дробь в формате 'numerator / denominator'
        if (denominator_ == 1)
            std::cout << numerator_;
        else if (denominator_ == 0)
            std::cout << "NaN";
        else if (numerator_ == 0)
            std::cout << "0";
        else
            std::cout << numerator_ << " / " << denominator_;

        return;
    }

    double calc() {  // Возвращает значение дроби в десятичном виде
        if (denominator_ == 0) return NAN;
        return numerator_ / denominator_;
    }

    int getNumerator() {  // Возвращает значение числителя
        return numerator_;
    }

    int getDenominator() {  // Возвращает знамечение знаменателя
        return denominator_;
    }

    ~Fraction(){};

private:
    int numerator_;
    int denominator_;
};

int main() {
    Fraction abc(1, 3);
    abc.printFraction();
    return 0;
}
