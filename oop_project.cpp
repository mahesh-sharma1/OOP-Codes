#include <iostream>
#include <fstream> //for file handling
#include <iomanip> //for manipulators
#include <string>
using namespace std;

class Product // Base class Product
{
protected:
    string name;
    float price;

public:
	
    Product() //Product class default constructor
    {
        name = "";
        price = 0.0;
    }
    
    Product(string n, float p) //Paramaterized constructor
    {
        name = n;
        price = p;
    }

    void getDetails(string n, float p) //gettng the details
    {
        name = n;
        price = p;
    }

    string getName() //using this function to access the private members of product class in it's derived classes
    {
        return name;
    }
    
    float getPrice() //same as above
    {
        return price;
    }

    virtual void display() //function which can be overriden
    {
        cout << setw(15) << left << name << setw(10) << fixed << setprecision(2) << price << endl; //left is a manipulator which aligns the text to left just used to make it look organized if not used also no problem just the text will align defultly at right
    }
    
};


class Beverage : public Product // Derived class Beverage
{
    string flavor;
    string size;

public:
    Beverage() : Product() //default constructor which initialized both base and derived classes members
    {
        flavor = "";
        size = "";
    }
    Beverage(string n, float p, string f, string s) : Product(n, p) //parametarized constructors
    {
        flavor = f;
        size = s;
    }

    void setBeverage(string n, float p, string f, string s) //function to enter the details
    {
        getDetails(n, p);
        flavor = f;
        size = s;
    }

    void display()
    {
        cout << setw(15) << left << name << setw(10) << price << setw(10) << flavor << setw(10) << size << endl;
    }
    
};


class Customer // Customer class
{
    string name;
    string phone;

public:
    void setCustomer(string n, string p) //function to initialize the members 
    {
        name = n;
        phone = p;
    }

    void displayCustomer()
    {
        cout << "Customer Name: " << name << endl;
        cout << "Phone Number : " << phone << endl;
    }
};


class Bill // Bill class
{
    Beverage beverages[10]; //object of class beverage
    int quantities[10];
    int itemCount;
    float taxRate = 0.13;
    float discountRate = 0.10;

public:
    Bill() //default constructor
    {
        itemCount = 0;
    }

    void addItem(Beverage b, int qty) //setting the items for maximum number of 10 items
    {
        if (itemCount < 10)
        {
            beverages[itemCount] = b;
            quantities[itemCount] = qty;
            itemCount++;
        }
        else
        {
            cout << "Maximum item limit reached!" << endl;
        }
    }

    void generateBill(Customer c) //final bill
    {
        float final_total = 0.0;
        cout << "\n========== BILL ==========\n";
        c.displayCustomer();
        cout << "\nItems:\n";
        cout << setw(15) << left << "Name" << setw(10) << "Price" << setw(10) << "Flavor" << setw(10) << "Size" << setw(10) << "Qty" << setw(10) << "Total" << endl;

        for (int i = 0; i < itemCount; i++)
        {
            float itemTotal = beverages[i].getPrice() * quantities[i];
            final_total += itemTotal;
            cout << setw(15) << beverages[i].getName() << setw(10) << beverages[i].getPrice()
                 << setw(10) << "N/A" // Displaying "N/A" for flavor and size
                 << setw(10) << "N/A"
                 << setw(10) << quantities[i]
                 << setw(10) << itemTotal << endl;
        }

        float tax = final_total * taxRate;
        float discount = final_total * discountRate;
        float total = final_total + tax - discount;

        cout << "\nFinal total : " << final_total;
        cout << "\nTax (13%): " << tax;
        cout << "\nDiscount : " << discount;
        cout << "\nTotal    : " << total << endl;

        ofstream fout("bill.txt", ios::app); // file open in append mode i.e we can add from where we left
        fout << "Customer: " << "\n";
        fout << "Items: " << itemCount << ", Total: " << total << "\n\n";
        fout.close();
    }
};


int main()
{
    
    Beverage menu[6]; // Already defined beverage menu for 6 items
    menu[0].setBeverage("Coke", 80, "Classic", "Small");
    menu[1].setBeverage("Lassi", 70, "Orange", "Medium");
    menu[2].setBeverage("Cold Coffee", 100, "Mocha", "Large");
    menu[3].setBeverage("Hot Coffee", 80, "Mocha", "Medium");
    menu[4].setBeverage("Black Tea", 20, "Mocha", "SMall");
    menu[5].setBeverage("Milk Tea", 30, "Green", "Medium");

    Customer c;
    string name, phone;
    cout << "Enter Customer Name: ";
    getline(cin, name);
    cout << "Enter Phone Number: ";
    getline(cin, phone);
    c.setCustomer(name, phone);

    cout << "\nAvailable Beverages:\n";
    cout << setw(5) << left << "ID" << setw(15) << "Name" << setw(10) << "Price" << setw(10) << "Flavor" << setw(10) << "Size" << endl; //setw is used to allow the space between each terms since it allocates how much space one can take here we are using it instead of \t because \t was not making it look organized

    for (int i = 0; i < 6; i++)
    {
        cout << setw(5) << i + 1;
        menu[i].display();
    }

    Bill bill;
    int choice, qty;

    do
    {
        cout << "\nEnter Beverage ID to add to bill (0 to submit): ";
        cin >> choice;

        if (choice >= 1 && choice <= 6)
        {
            cout << "Enter quantity: ";
            cin >> qty;
            bill.addItem(menu[choice - 1], qty);
        }
    } while (choice != 0);

    bill.generateBill(c); //generate bill with all the details

    return 0;
}

