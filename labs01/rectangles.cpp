#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Point {
 unsigned long long x, y;

 Point (unsigned long long x , unsigned long long y):
 x(x) , y(y) {}

 Point minx (Point const &rha ) const {
 return Point ( rha.x < x ? rha.x : x, y);
    }

 Point miny (Point const &rha) const {
        return Point (x , rha . y < y ? rha.y : y);
    }

    Point maxx(Point const &rha ) const {
        return Point (rha . x > x ? rha.x : x, y);
    }

    Point maxy(Point const &rha ) const {
        return Point (x , rha.y > y ? rha.y : y);
    }

    void print ( ) const {
        cout << "("<< x << ","<< y << ")";
    }

};



class Rectangle {
    public:
    Point p;

    Rectangle(): p(Point (0, 0)){}

    Rectangle(Point const& h): p(h){}

    Rectangle operator+(Rectangle const &rha) const {
        unsigned long long XmAx = rha.p.maxx(p).x;
        unsigned long long YmAx = rha.p.maxy(p).y;
        Point p1(XmAx, YmAx);
        return Rectangle(p1);
    }

    Rectangle operator*(Rectangle const &rha) const {
        unsigned long long XmIn = rha.p.minx(p).x;
        unsigned long long YmIn = rha.p.miny(p).y;
        Point p1(XmIn, YmIn);
        return Rectangle(p1);
    }

    Rectangle operator+=(Rectangle const &rha) const {
        unsigned long long XmAx += rha.p.maxx(p).x;
        unsigned long long YmAx += rha.p.maxy(p).y;
        Point p1(XmAx, YmAx);
        return Rectangle(p1);
    }
    /*const Rectangle& operator=(const Rectangle& other) const {
        *(const_cast<unsigned long long*>(&(p.x))) = other.p.x;
        *(const_cast<unsigned long long*>(&(p.y))) = other.p.y;
        return *this;
    };*/

    void print() const {
        p.print();
    }
};

int main()
{
    int lastnumber = 0, lastsimvol = 0;
    int length = 0;
    Rectangle R(Point(0,0));
    //R.print();
    std::string expression ;
    std::getline(std::cin, expression);
    length = expression.length();
    //std::cout<<expression;
    char* number = new char[length];
    char* simvol = new char[length];
    for(int i=0; i<length; i++){
        if(int(expression[i]) >= 48 and int(expression[i]) <= 57){
            number[lastnumber] = expression[i];
            lastnumber++;
        }
        else if(expression[i]!=',' and expression[i]!='(' and expression[i]!=')' and expression[i]!=' '){
            simvol[lastsimvol] = expression[i];
            lastsimvol++;
        }
    }

    Rectangle* r = new Rectangle[lastnumber/2];

    for (int i = 0; i < lastnumber/2; i++){
        int x = number[i*2] - '0';
        int y = number[i*2+1] - '0';
        //std::cout<<x<<" "<<y;
        r[i] = Rectangle(Point(x, y));

    }

    for(int i = 0; i<lastsimvol; i++){
        if (simvol[i] == '*'){
            r[i] = r[i] * r[i+1];
            r[i+1] = Rectangle(Point(0,0));

        }
    }
    for(int i = 0; i<lastnumber/2; i++){
        R = R + r[i];
    }
    R.print();
    delete[] number, simvol;
    return 0;
}
