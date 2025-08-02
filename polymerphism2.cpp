/*Suppose you are building a simple drawing application. You have a base class
called Shape and two derived classes called Circle and Square. Each class has a
member function void draw()that should print the shape's name followed by " is
drawn." Create the necessary classes with appropriate member functions and
inheritance relationships. Then, write a program that demonstrates the concept
of runtime polymorphism by using an array of pointers to Shape objects, where
some pointers point to Circle objects and some to Square objects. Use these
pointers to call the draw() function for each object.*/
#include <iostream>
using namespace std;
class Shape
{
public:
    virtual void draw()
    {
        cout << "Shape class";
    }
};
class Circle : public Shape
{
public:
    void draw()
    {
        cout << "Circle is drawn." << endl;
    }
};
class Square : public Shape
{
public:
    void draw()
    {
        cout << "Square is drawn." << endl;
    }
};
int main()
{
    Circle c;
    Square sq;
    Shape *s[2] = {&c, &sq};
    for (int i = 0; i < 2; i++)
    {
        s[i]->draw();
    }
    return 0;
}