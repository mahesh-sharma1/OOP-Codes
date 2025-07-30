/*You are provided with a Time class that represents time in hours and
minutes. The class has two private member variables: hours (to store the
time in hours) and minutes (to store the time in minutes). Your task is to
implement a member function that allows conversion from Time to int,
representing the total minutes.*/
#include <iostream>
using namespace std;
class Time
{
    int hours, minutes;

public:
    Time()
    {
        hours = 0;
        minutes = 0;
    }
    Time(int h, int m)
    {
        hours = h;
        minutes = m;
    }
    operator int()
    {
        return (hours * 60 + minutes);
    }
};
int main()
{

    Time t(5, 40);
    int totalminutes = t;
    cout << "The total minutes is: " << totalminutes;
    return 0;
}