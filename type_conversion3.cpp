/*Create a class Journey with two private data members: distanceInMeters
(of type double) and timeInSeconds (of type double). Also, create another
class Speed with two private data members: metersPerSecond (of type
double) and kilometersPerHour (of type double).You are required to
implement two different approaches to convert an object of type Journey
into an object of type Speed:
i. Using a One-Argument Parameterized Constructor
ii. Using a Casting Operator Function
Demonstrate both conversions in the main() function.
metersPerSecond=distanceInMeter/timeInSeconds
kilometersPerHour=metersPerSecond×3.6*/
#include <iostream>
using namespace std;

class Speed; // Forward declaration

class Journey
{
private:
    double distanceInMeters;
    double timeInSeconds;

public:
    Journey(double d, double t)
    {
        distanceInMeters = d;
        timeInSeconds = t;
    }

    double getDistance() const { return distanceInMeters; }
    double getTime() const { return timeInSeconds; }

    void display() const
    {
        cout << "Journey - Distance: " << distanceInMeters << " m, Time: " << timeInSeconds << " s" << endl;
    }

    // Casting operator (Approach ii)
    operator Speed();
};

class Speed
{
private:
    double metersPerSecond;
    double kilometersPerHour;

public:
    // Constructor from Journey (Approach i)
    explicit Speed(const Journey &j)
    {
        metersPerSecond = j.getDistance() / j.getTime();
        kilometersPerHour = metersPerSecond * 3.6;
    }

    // Constructor used by casting operator
    Speed(double mps, double kph)
    {
        metersPerSecond = mps;
        kilometersPerHour = kph;
    }

    void display() const
    {
        cout << "Speed - " << metersPerSecond << " m/s, " << kilometersPerHour << " km/h" << endl;
    }
};

// Casting operator implementation (Approach ii)
Journey::operator Speed()
{
    double mps = distanceInMeters / timeInSeconds;
    double kph = mps * 3.6;
    return Speed(mps, kph);
}

int main()
{
    Journey j1(1000, 200); // 1000 meters in 200 seconds
    j1.display();

    // Conversion using casting operator
    Speed s1 = j1; // uses Journey::operator Speed()
    cout << "\nUsing casting operator:\n";
    s1.display();

    // Conversion using parameterized constructor
    Speed s2(j1); // uses Speed(Journey) constructor
    cout << "\nUsing parameterized constructor:\n";
    s2.display();

    return 0;
}
