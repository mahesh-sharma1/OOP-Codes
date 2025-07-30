/*You are provided with a Height class that represents a person's height in
the feet-inch system. The class has two private member variables: feet (to
store the height in feet) and inches (to store the height in inches). Your task
is to implement a constructor that allows conversion from int (representing
height in inches) to Height. Try to implement given conversion using
explicit constructor.*/
#include <iostream>
using namespace std;
class Height
{
    int feet, inches;

public:
    Height()
    {
        feet = 0;
        inches = 0;
    }
    explicit Height(int i)
    {
        feet = i / 12;
        inches = i % 12;
    }
    void display()
    {
        cout << "The height is: " << feet << " ft " << inches << " inch" << endl;
    }
};
int main()
{
    int totalinches;
    cout << "Enter the total inches: ";
    cin >> totalinches;
    Height h(totalinches);
    h.display();
    return 0;
}