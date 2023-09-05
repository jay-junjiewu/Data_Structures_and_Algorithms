#include <iostream>

using namespace std;

/*
Abstraction: "displaying” only the relevant attributes of objects and “hides” the unnecessary details
    User just need to know which methods are available and which input parameters are needed 
    Do not need to understand how the method is implemented
    Methods that are abstraction do not "seem to change" for the user, 
        we can cahnge the entire implementation as long as the interface reamins same for user

Abstract Layer can be implemented using abstract classes
    Abstract class in C++ is a class with at least one pure virtual function
    We cannot create instances of an abstract classes but we can create pointers of abstract classes
*/

class SmartPhone {
public:
    virtual void Take_Picture() = 0;
};
class Android : public SmartPhone {
public:
    void Take_Picture() {
        cout << "Android Picture" << endl;
    }
};
class iPhone : public SmartPhone {
public:
    void Take_Picture() {
        cout << "iPhone Picture" << endl;
    }
};

int main(void) {
    // The implementation of Take_Picture() function is independent in its derived classes
    // User just uses Take_Picture() foe each device and doesn't not need to know the different implementations behind it
    SmartPhone *s1 = new Android();
    s1->Take_Picture();

    SmartPhone *s2 = new iPhone();
    s2->Take_Picture();

    return 0;
}