#include <iostream>
#include <string>
#include <list>

using namespace std;

/*
Operator Overloading: Defines how a certain operator function will interact with a specific datatype
Operator Functions: Just like regular functions except that they are named operator<symbol>
*/
// Note that members of a structure are public by default while members of a class are private by default

// Using structs

struct SmartPhone {
    string Brand;
    int Year;
    // Constructor
    SmartPhone(string Brand, int Year) {
        this->Brand = Brand;
        this->Year = Year;
    }
    // Overloading operator == for type SmartPhone
    // const is used to ensure that the function will not change its parameters
    const bool operator==(const SmartPhone &s) {
        return this->Brand == s.Brand && this->Year == s.Year;
    }
};
// Overloading insertion operator (<<) for type SmartPhone
// Insertion operator works with two operand objects, pass by reference
// The parameter COUT is different from the cout in standard library
// Returns an ostream object so that we can use multiple insertion operators like "cout << s1 << s2;"
// Global function since first operand is of type ostream and it overloads for all datatype we want to use operator with
ostream &operator<<(ostream &COUT, SmartPhone &s) {
    COUT << "Brand: " << s.Brand << endl;
    COUT << "Year: " << s.Year << endl;
    return COUT;
}

struct PhoneCollection {
    list<SmartPhone> myPhones;
    // Overloading += operator for type PhoneCollection
    // += operator works with one operand object, pass by reference
    // Function is a member of the struct since first operand is a member of the struct
    void operator+=(SmartPhone &s) {
        this->myPhones.push_back(s);
    }
    // Overloading -= operator for type PhoneCollection
    // Just overloading -= will throw an error "no match for operator =="
    // Type definition for remove() uses the == operator which need to be overloaded for Smartphone object
    /*
        auto remove(const _Ty& _Val) { // erase each element matching _Val
            return remove_if([&](const _Ty& _Other) { return _Other == _Val; });
        }
    */
    void operator-=(SmartPhone &s) {
        this->myPhones.remove(s);
    }
};
// Overloaded operator << for type PhoneCollection
ostream &operator<<(ostream &COUT, PhoneCollection &phoneCollection) {
   for(SmartPhone s : phoneCollection.myPhones) {
        COUT << s;
   }
   return COUT;
}


// Using classes

class Laptop {
private: 
    string Brand;
    int Year;
public:
    // Constructor
    Laptop(string Brand, int Year) {
        this->Brand = Brand;
        this->Year = Year;
    }

    // Friend class
    friend class Friend_Class;
    // Friend function
    friend int get_Year(Laptop l);
    
    // Overloading operator == for type Laptop
    const bool operator==(const Laptop &l) {
        return this->Brand == l.Brand && this->Year == l.Year;
    }
};
// Friend class to access the private members
class Friend_Class {
public: 
    string get_Brand(Laptop l) {
        return l.Brand;
    }
};
// Friend function to access the private members
int get_Year(Laptop l) {
        return l.Year;
}
// Overloaded operator << for type Laptop
ostream &operator<<(ostream &COUT, Laptop &l) {
    // Cannot use l.Brand since members are private and can be accessed through friend class or friend function
    Friend_Class f;
    COUT << "Brand: " << f.get_Brand(l) << endl;    // Through friend class object
    COUT << "Year: " << get_Year(l) << endl;        // Through friend function
    return COUT;
}

struct LaptopCollection {
    list<Laptop> myLaptop;
    // Overloading += operator for type LaptopCollection
    void operator+=(Laptop &l) {
        this->myLaptop.push_back(l);
    }
    // Overloading -= operator for type LaptopCollection
    void operator-=(Laptop &l) {
        this->myLaptop.remove(l);
    }
};
// Overloaded operator << for type LaptopCollection
ostream &operator<<(ostream &COUT, LaptopCollection &laptopCollection) {
   for(Laptop l : laptopCollection.myLaptop) {
        COUT << l;
   }
   return COUT;
}


int main(void) {

    // Using struct

    // Operator Overloading on structs (default public members)
    SmartPhone *s1 = new SmartPhone("Huawei", 2021);     // Pointer to object of type SmartPhone
    SmartPhone s2 = SmartPhone("Apple", 2022);           // Object of type SmartPhone
    // operator<<(cout,s1);  is equivalent to cout << s1;
    cout << *s1 << s2 << endl;   // Overloaded operator << for type SmartPhone
    
    PhoneCollection phoneCollection;
    phoneCollection += *s1;          // Overloaded operator +=, adds the SmartPhone object to the list
    phoneCollection += s2;
    phoneCollection -= s2;           // Overloaded operator -=, removes the SmartPhone object from the list
    cout << phoneCollection << endl; // Overloaded operator << for type PhoneCollection


    // Using class

    // Operator Overloading on classes (default private members)
    Laptop *l1 = new Laptop("Acer", 2023);  // Pointer to object type Laptop
    Laptop l2 = Laptop("Dell", 2020);       // Object of type Laptop
    cout << *l1 << l2 << endl;  // Overloaded operator << for type Laptop

    LaptopCollection laptopCollection;
    laptopCollection += *l1;
    laptopCollection += l2;
    laptopCollection -= l2;
    cout << laptopCollection << endl;

    return 0;
}