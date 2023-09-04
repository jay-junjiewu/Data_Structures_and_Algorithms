#include <iostream>
#include <list>

using namespace std;

// Note that we need to use g++ compiler for C++ file (not gcc), change it in the tasks.json file

/* 
Public: Any member can access
Protected: Only members in the same class or derived class can access
Private: Only members in same class can access

Constructor: a special function that creates an instance (object) of the class

Encapsulation: bundling of data with the mechanisms or methods that operate on the data
                also refer to the limiting of direct access of that data (private variables)

Inheritance: Reusing and extending existing classes without modifying them, producing hierarchical relationships between them
    Public Inheritance: Public and protected members of the base class remain public and protected in derived class
    Protected Inheritance: Public and protected members of the base class become protected members of the derived class
    Private Inheritance: Public and protected members of the base class become private members of the derived class
        A base class's private members are never accessible directly from a derived class, only through public or protected functions in base class


*/

class Vehicle{
private:
    list<string> History;
protected:
    int Year;
public:
    // Constructor
    Vehicle(int Year) {
        // Sets the private class variable equal to the constructor parameter
        this->Year = Year;
    }
    // Accessors (Get)
    void Get_Info() {
        cout << "Year: " << Year << endl;
        cout << "Model: ";
        for(string history : History) {
            cout << history << "  ";
        }
        cout << endl;
    }
    // Mutators (Set)
    void Set_History(string title) {
        History.push_back(title);
    }
};

// Derived class inherits the public members of the base class
class Electric_Car: public Vehicle {
public:
    Electric_Car(int Year):Vehicle(Year) {
        
    }
    void Charge() {
        cout << "Vehicle from year " << Year << " is charging..." << endl;
    }
};

int main() {

    Vehicle v1(2020);
    v1.Set_History("History A");
    v1.Set_History("History B");
    v1.Get_Info();
    //v1.Charge(); will throw an error since the base class cannot access elements of the derived class

    Electric_Car e1(2021);
    e1.Set_History("History X");
    e1.Set_History("History Y");
    e1.Get_Info();
    e1.Charge();

    Electric_Car e2(2022);
    e2.Charge();

    return 0;
}