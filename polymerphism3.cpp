/*You are developing a simulation of a zoo, and you want to represent different
animals using classes. You have a base class called Animal which contains a
pure virtual function makeSound() that each derived class needs to implement.
You also have two derived classes, Lion and Elephant, both inheriting from the
Animal class. Create the necessary classes with appropriate member functions
and inheritance relationships. Then, write a program that demonstrates the
concept of pure virtual functions by using an array of pointers to Animal objects,
where some pointers point to Lion objects and some to Elephant objects. Use
these pointers to call the makeSound() function for each object.*/
#include <iostream>
using namespace std;
class Animal
{
public:
    virtual void makeSound() = 0;
};
class Lion : public Animal
{
public:
    void makeSound()
    {
        cout << "Lion Roars" << endl;
    }
};
class Elephant : public Animal
{
    void makeSound()
    {
        cout << "Elephant Snorts" << endl;
    }
};
int main()
{
    Lion l;
    Elephant e;
    Animal *a[2] = {&l, &e};
    for (int i = 0; i < 2; i++)
    {
        a[i]->makeSound();
    }
    return 0;
}