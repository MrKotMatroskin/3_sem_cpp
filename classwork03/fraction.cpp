#include <iostream>
using namespace std;
class Fraction
{
public:
    friend std::ostream &operator<<(std::ostream &out, const Fraction &obj)
    {
        out << obj.numerator << " / " << obj.denominator << endl;
        return out;
    } // Оператор вывода << "числитель знаминатель

    friend std::istream &operator>>(std::istream &is, Fraction &obj)
    {
        is >> obj.numerator >> obj.denominator;
        return is;
    } // Оператор ввода >> числитель >> знаминатель

    Fraction& operator+=(const Fraction &other)
    {
        numerator = numerator * other.denominator + denominator * other.numerator;
        denominator *= other.denominator;
        fracSimplify();
        return *this;
    }

    Fraction& operator-=(const Fraction &other)
    {
        numerator = numerator * other.denominator - denominator * other.numerator;
        denominator *= other.denominator;
        fracSimplify();
        return *this;
    }

    Fraction& operator*=(const Fraction &other)
    {
        numerator *= other.numerator;
        denominator *= other.denominator;
        fracSimplify();
        return *this;
    }

    Fraction operator+(const Fraction &other) const
    {
        Fraction temp = *this;
        temp += other;
        return temp;
    }

    Fraction operator-(const Fraction &other) const
    {
        Fraction temp = *this;
        temp -= other;
        return temp;
    }

    Fraction operator*(const Fraction &other) const
    {
        Fraction temp = *this;
        temp *= other;
        return temp;
    }

    Fraction& operator++()
    {
        return *this += 1;
    }

    Fraction operator++(int)
    {
        Fraction result = *this;
        ++(*this);
        return result;
    }

    Fraction& operator--()
    {
        return *this -= 1;

    }
    Fraction operator--(int)
    {
        Fraction result = *this;
        --(*this);
        return result;
    }

    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}

    Fraction(int numerator) : numerator(numerator), denominator(1) {} // Делигирующий конструктор

    Fraction() = delete;                                // Конструктор по умолчанию должен быть удален

    Fraction(const Fraction &other): numerator(other.numerator), denominator(other.denominator) { }// Конструктор копирования

    void fracSimplify()
    { // Сокращает дробь по возможности
        int num = abs(numerator), denum = abs(denominator), nod;
        while ((num != 0) and (denum != 0)){
            if (num > denum){
                num = num % denum;
            }
            else {
                denum = denum % num;
            }
        }
        nod = num + denum;

        denominator = denominator / nod;
        numerator = numerator / nod;
    }
    double calc()
    { // Возвращает значение дроби в десятичном виде
        return (double(numerator) / double(denominator));
    }

    int getNumerator()
    { // Возвращает значение числителя
        return numerator;
    }

    int getDenominator()
    { // Возвращает знамечение знаменателя
        return denominator;
    }

private:
    int numerator;
    int denominator;
};
int main()
{

}
