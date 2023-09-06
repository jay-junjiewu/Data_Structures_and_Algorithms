#include <iostream>
#include <string>

using namespace std;

// Abstract base class
class Student {
public:
    string Name;
    int Age;
    char Gender;
    virtual void Study() = 0;
};

class ComputerScience : public Student {
public:
    void Study() {
        cout << "Coding..." << endl;
    }
};
class Engineering : public Student {
public:
    void Study() {
        cout << "Engineering..." << endl;
    }
};
class Humanities : public Student {
public:
    void Study() {
        cout << "Sleeping..." << endl;
    }
};


int main(void) {
    // Array of Student class pointers
    Student *s[3];
    s[0] = new ComputerScience();
    s[1] = new Engineering();
    s[2] = new Humanities();

    // Invoke Study() on base class array but since elements of the array are derived classes,
    // polymorphism allows every Student type to invoke its own implementation of Study()
    for(int i = 0; i < 3; i++) {
        s[i]->Study();
    }

    // Deallocating memory
    for(int i = 0; i < 3; i++) {
        delete s[i];
    }

    return 0;
}