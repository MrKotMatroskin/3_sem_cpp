#include <iostream>
using namespace std;
class Fraction
{
public:
    friend std::ostream &operator<<(std::ostream &out, const Fraction &obj)
    {
        out << obj.numerator << " / " << obj.denominator << endl;
        return out;
    } // �������� ������ << "��������� �����������

    friend std::istream &operator>>(std::istream &is, Fraction &obj)
    {
        is >> obj.numerator >> obj.denominator;
        return is;
    } // �������� ����� >> ��������� >> �����������

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

    Fraction(int numerator) : numerator(numerator), denominator(1) {} // ������������ �����������

    Fraction() = delete;                                // ����������� �� ��������� ������ ���� ������

    Fraction(const Fraction &other): numerator(other.numerator), denominator(other.denominator) { }// ����������� �����������

    void fracSimplify()
    { // ��������� ����� �� �����������
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
    { // ���������� �������� ����� � ���������� ����
        return (double(numerator) / double(denominator));
    }

    int getNumerator()
    { // ���������� �������� ���������
        return numerator;
    }

    int getDenominator()
    { // ���������� ���������� �����������
        return denominator;
    }

private:
    int numerator;
    int denominator;
};
int main()
{

}
