#include <iostream>
#include <cmath>

using namespace std;

/*
Can access private members outside the class by making them public, through public "get functions", or friend functions

Friend Function: Not a member of the class, a friend, has access to all private and protected members of the class
Friend Class: Can access private and protected members of other classes in which it is declared as a friend

Friendship is not mutual, a friend class of the base class can access all members of the class but the base class cannot 
    access private and protected members of the friend class unless the friend class declares the base class as a friend

Friendship is not inherited, a friend of the base class, by default, won't be a friend of the derived class
*/

class EquilateralTriangle {
private:
    float side;
    float perimeter;
    float area;
public:
    void set_side(float side) {
        this->side = side;                  // Need to use "this" keyword
        this->perimeter = side * 3;     // "this" keyword optional
        area = (sqrt(3) * side * side) /4;  // "this" keyword optional
    }
    // Friend function of the EquilateralTriangle class
    friend void print_perimeter(EquilateralTriangle et);

     // Friend class of the EquilateralTriangle class
    friend class Friend_Class;
};

void print_perimeter(EquilateralTriangle et) {
    cout << "Perimeter: " << et.perimeter << endl;
}

class Friend_Class {
public: 
    void print_area(EquilateralTriangle et) {
        cout << "Area: " << et.area << endl;
    }
};

int main(void) {

    EquilateralTriangle et1;
    et1.set_side(3);

    print_perimeter(et1);      // friend function

    Friend_Class f;
    f.print_area(et1);         // function in a freind class
    
    return 0;
}