/*Create a base class Employee with a member name and a function display()
to print the name. Derive a class Manager from Employee that adds a member
department and overrides the display() function to print both name and
department. In main()function create a Manager object, assign its address to
a Employee* pointer. Set the name using the base class pointer. Try setting
the department using the base class pointer and observe what happens. Call
the display() function using both base and derived class pointers.
i. Explain why department cannot be accessed through the base class
pointer.
ii. What happens if display() is not declared as virtual in the base class?*/
#include <iostream>
#include <string>
using namespace std;
class Employee
{
public:
    string name;
    virtual void display()
    {
        cout << "Name: " << name << endl;
    }
};
class Manager : public Employee
{
public:
    string department;
    void display()
    {
        cout << "Name: " << name << " Department: " << department << endl;
    }
};
int main()
{
    Employee *e;
    Manager m;
    e = &m;
    e->name = "Mahesh";
    m.department = "CSIT";
    e->display();

    Manager *ma;
    ma = &m;
    ma->display();
    return 0;
}