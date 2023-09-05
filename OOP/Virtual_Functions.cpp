#include <iostream>

using namespace std;

/*
Base class is instrument and inherited/derived class is Piano
Polymorphism is applied on the MakeSound() function (it is overwritten in the derived class)

Virtual function: Function that is defined in base class and redefined in derived class and has runtime polymorphism
    It allows us to execute the most derived version of the function using a base class pointer
    By changing the MakeSound() function in the base class into a virtual function, 
    it executes the most derived version when it is invoked using a base class pointer

Pure Virtual function: No implementation in base class and forces its derived class to have their own implementation
    PlaySong() is a pure virtual function, making the class is an abstract class 
    An abstract class in C++ is a class with at least one pure virtual function
    We cannot create objects of an abstract class
*/

class Instrument {
    public:
    // Virtual function
    virtual void MakeSound() {
        cout << "Instrument sound" << endl;
    }
    // Pure virtual function
    virtual void PlaySong() = 0;
}; 

class Guitar : public Instrument {
    public:
    void MakeSound() {
        cout << "Guitar sound" << endl;
    }
    virtual void PlaySong() {
        cout << "Guitar is playing song" << endl;
    }
};

class Piano : public Instrument {
    public:
    virtual void PlaySong() {
        cout << "Piano is playing song" << endl;
    }
};

int main(void) {
    Instrument *i1 = new Guitar();
    i1->MakeSound();    // if virtual: Derived class implementation, if not virtual: Base class implementation
    i1->PlaySong();

    cout << endl;


    Instrument *i2 = new Piano();
    i2->MakeSound();    // derived class has no implementation of MakeSound() so base class function is inherited
    i2->PlaySong();

    cout << endl;

    // Runtime Polymorphism using virtual functions
    Instrument *ins[2] = {i1, i2};  // Array of type instrument pointers
    for(int i = 0; i < 2; i++) {
        ins[i]->MakeSound();
    }

    return 0;
}