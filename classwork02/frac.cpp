#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <iostream>

class Fraction {
    public:
        Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {};
        
        Fraction(int numerator): numerator_(numerator), denominator_(1) {}
        Fraction(const Fraction& other) {
            numerator_ = other.numerator_;
            denominator_ = other.denominator_;
        }
    
        void printFraction() {  // Выводит дробь в формате 'numerator / denominator'
        if (denominator_ == 1)
            std::cout << numerator_;
        else if (denominator_ == 0) 
            std::cout << "NaN";
        else if (numerator_ == 0) 
            std::cout << 0;
        else
            std::cout << numerator_<< " / " << denominator_;

        return;
    }
    
        void fracReverse() {
            int tmp = numerator_;
            numerator_ = denominator_;
            denominator_ = tmp;
        }
    
        void fracSimplify() {  // Сокращает дробь по возможности
            int a = numerator_;
            int b = denominator_;
            if (a < b)
                std::swap(a, b);
            while(b) {
                a %= b;
                std::swap(a, b);
            }

            numerator_ /= a;
            denominator_ /= a;
        }
    
        void multByNumber(int value) {
            numerator_ *= value;
            fracSimplify();
        }
    
        void multByFrac(const Fraction& other) {
            denominator_ *= other.denominator_;
            numerator_ *= other.numerator_;
            fracSimplify();
        }
    
        Fraction multByFracReturn(const Fraction& other) const {
            int newDenominator = denominator_ * other.denominator_;
            int newNumerator = numerator_ * other.numerator_;
            Fraction newFrac(newNumerator, newDenominator);
            newFrac.fracSimplify();
            return newFrac;
        }
    
        void sumFrac(const Fraction& other) {
            int a = other.denominator_;
            int b = denominator_;
            if (a < b)
                std::swap(a, b);
            while(b) {
                a %= b;
                std::swap(a, b);
            }
            int lcm = (denominator_ * other.denominator_) / a;
            int mulfirst = lcm / denominator_;
            int mulsecond = lcm / other.denominator_;
            numerator_ = numerator_ * mulfirst + other.numerator_ * mulsecond;
            denominator_ = lcm;
            fracSimplify();
        }
    
        Fraction sumFracReturn(const Fraction& other) const {
            int a = other.denominator_;
            int b = denominator_;
            if (a < b)
                std::swap(a, b);
            while(b) {
                a %= b;
                std::swap(a, b);
            }
            int lcm = (denominator_ * other.denominator_) / a;
            int mulfirst = lcm / denominator_;
            int mulsecond = lcm / other.denominator_;
            Fraction newFrac(numerator_ * mulfirst + other.numerator_ * mulsecond, lcm);
            newFrac.fracSimplify();
            return newFrac;
        }
    
        void diffFrac(const Fraction& other) {
            Fraction copy(other);
            copy.multByNumber(-1);
            sumFrac(copy);
        }
    
        Fraction diffFracReturn(const Fraction& other) const {
            Fraction copy(other);
            copy.multByNumber(-1);
            return sumFracReturn(copy);
        }
    
        double calc() {
            if (denominator_ == 0) return NAN;
            return numerator_ / denominator_;
        }

        int getNumerator() { 
            return numerator_;
        }

        int getDenominator() {
            return denominator_;
        }
    
    private:
        int numerator_;
        int denominator_;
};


int main() {
    int n1, d1, n2, d2;
    std::cin >> n1 >> d1 >> n2 >> d2;
    Fraction f1(n1, d1);
    Fraction f2(n2, d2);
    Fraction f3 = f2.multByFracReturn(f1);
    f3.printFraction();
    return 0;
}