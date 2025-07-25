#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <limits> // for std::numeric_limits

class Product
{
protected:
    std::string name;
    double pricePerUnit;
    int quantity;

public:
    Product(const std::string &name, double pricePerUnit, int quantity);
    virtual ~Product() {}

    virtual double calculateTotalPrice() const = 0;
    virtual void display() const;

    std::string getName() const;
    double getPricePerUnit() const;
    int getQuantity() const;
    void setName(const std::string &name);
    void setPricePerUnit(double pricePerUnit);
    void setQuantity(int quantity);
};

Product::Product(const std::string &name, double pricePerUnit, int quantity)
    : name(name), pricePerUnit(pricePerUnit), quantity(quantity) {}

void Product::display() const
{
    std::cout << "Product: " << name << ", Price per unit: " << pricePerUnit << ", Quantity: " << quantity << std::endl;
}

std::string Product::getName() const { return name; }
double Product::getPricePerUnit() const { return pricePerUnit; }
int Product::getQuantity() const { return quantity; }
void Product::setName(const std::string &name) { this->name = name; }
void Product::setPricePerUnit(double pricePerUnit) { this->pricePerUnit = pricePerUnit; }
void Product::setQuantity(int quantity) { this->quantity = quantity; }

class Beer : public Product
{
private:
    double alcoholContent;

public:
    Beer(const std::string &name, double pricePerBottle, int quantity, double alcoholContent);
    double calculateTotalPrice() const override;
    void display() const override;

    double getAlcoholContent() const;
    void setAlcoholContent(double content);
};

Beer::Beer(const std::string &name, double pricePerBottle, int quantity, double alcoholContent)
    : Product(name, pricePerBottle, quantity), alcoholContent(alcoholContent)
{
    if (alcoholContent < 0 || alcoholContent > 100)
    {
        throw std::invalid_argument("Alcohol content must be between 0 and 100");
    }
}

double Beer::calculateTotalPrice() const
{
    if (pricePerUnit < 0 || quantity < 0)
    {
        throw std::runtime_error("Price and quantity must be positive values");
    }
    return pricePerUnit * quantity;
}

void Beer::display() const
{
    std::cout << "Beer ";
    Product::display();
    std::cout << "Alcohol Content: " << alcoholContent << "%" << std::endl;
}

double Beer::getAlcoholContent() const { return alcoholContent; }
void Beer::setAlcoholContent(double content)
{
    if (content < 0 || content > 100)
    {
        throw std::invalid_argument("Alcohol content must be between 0 and 100");
    }
    alcoholContent = content;
}

class Customer
{
private:
    std::string name;
    std::string address;

public:
    Customer(const std::string &name, const std::string &address);
    void display() const;

    std::string getName() const;
    std::string getAddress() const;
    void setName(const std::string &name);
    void setAddress(const std::string &address);
};

Customer::Customer(const std::string &name, const std::string &address)
    : name(name), address(address)
{
    if (name.empty() || address.empty())
    {
        throw std::invalid_argument("Name and address cannot be empty");
    }
}

void Customer::display() const
{
    std::cout << "Customer: " << name << ", Address: " << address << std::endl;
}

std::string Customer::getName() const { return name; }
std::string Customer::getAddress() const { return address; }
void Customer::setName(const std::string &name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Name cannot be empty");
    }
    this->name = name;
}
void Customer::setAddress(const std::string &address)
{
    if (address.empty())
    {
        throw std::invalid_argument("Address cannot be empty");
    }
    this->address = address;
}

class Invoice
{
private:
    Customer customer;
    std::vector<Product *> items;

public:
    Invoice(const Customer &customer);
    ~Invoice();
    void addItem(Product *product);
    void generateInvoice() const;
    void saveInvoice(const std::string &filename) const;
};

Invoice::Invoice(const Customer &customer) : customer(customer) {}

Invoice::~Invoice()
{
    for (Product *item : items)
    {
        delete item;
    }
}

void Invoice::addItem(Product *product)
{
    if (product == nullptr)
    {
        throw std::invalid_argument("Cannot add null product");
    }
    items.push_back(product);
}

void Invoice::generateInvoice() const
{
    if (items.empty())
    {
        throw std::runtime_error("No items to generate invoice");
    }

    double total = 0;
    customer.display();
    for (const Product *item : items)
    {
        item->display();
        total += item->calculateTotalPrice();
    }
    std::cout << "Total: " << total << std::endl;
}

void Invoice::saveInvoice(const std::string &filename) const
{
    if (filename.empty())
    {
        throw std::invalid_argument("Filename cannot be empty");
    }

    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file for writing");
    }

    double total = 0;
    file << "Customer: " << customer.getName() << ", Address: " << customer.getAddress() << "\n";
    for (const Product *item : items)
    {
        file << item->getName() << ": " << item->getQuantity() << " @ " << item->getPricePerUnit()
             << " each = " << item->calculateTotalPrice() << "\n";
        total += item->calculateTotalPrice();
    }
    file << "Total: " << total << "\n";
}

// Function to read invoice file and display to console
void readInvoice(const std::string &filename)
{
    if (filename.empty())
    {
        throw std::invalid_argument("Filename cannot be empty");
    }

    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file for reading");
    }

    std::string line;
    std::cout << "\n--- Invoice Contents from File ---\n";
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
    std::cout << "----------------------------------\n";
}

// Menu
void displayMenu()
{
    std::cout << "\n=========================\n";
    std::cout << "|       MAIN MENU       |\n";
    std::cout << "=========================\n";
    std::cout << "| 1. Add Customer       |\n";
    std::cout << "| 2. Add Beer           |\n";
    std::cout << "| 3. Generate Invoice   |\n";
    std::cout << "| 4. Save Invoice       |\n";
    std::cout << "| 5. Read Invoice File  |\n";
    std::cout << "| 6. Exit               |\n";
    std::cout << "=========================\n";
    std::cout << "Choose an option: ";
}

int main()
{
    try
    {
        Customer customer("Default", "Default Address");
        Invoice invoice(customer);
        bool customerAdded = false;

        while (true)
        {
            displayMenu();
            int choice;
            std::cin >> choice;

            try
            {
                switch (choice)
                {
                case 1:
                {
                    std::string name, address;
                    std::cout << "Enter customer name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::cout << "Enter customer address: ";
                    std::getline(std::cin, address);
                    customer = Customer(name, address);
                    invoice = Invoice(customer);
                    customerAdded = true;
                    break;
                }
                case 2:
                {
                    if (!customerAdded)
                    {
                        std::cout << "Please add a customer first.\n";
                        break;
                    }
                    std::string productName;
                    double price;
                    int quantity;
                    double alcoholContent;

                    std::cout << "Enter beer name: ";
                    std::cin.ignore();
                    std::getline(std::cin, productName);

                    std::cout << "Enter price per bottle: ";
                    std::cin >> price;
                    if (price <= 0)
                        throw std::invalid_argument("Price must be positive");

                    std::cout << "Enter quantity: ";
                    std::cin >> quantity;
                    if (quantity <= 0)
                        throw std::invalid_argument("Quantity must be positive");

                    std::cout << "Enter alcohol content (%): ";
                    std::cin >> alcoholContent;

                    invoice.addItem(new Beer(productName, price, quantity, alcoholContent));
                    break;
                }
                case 3:
                    invoice.generateInvoice();
                    break;
                case 4:
                {
                    std::string filename;
                    std::cout << "Enter filename: ";
                    std::cin >> filename;
                    invoice.saveInvoice(filename);
                    std::cout << "Invoice saved successfully to " << filename << std::endl;
                    break;
                }
                case 5:
                {
                    std::string filename;
                    std::cout << "Enter filename to read: ";
                    std::cin >> filename;
                    readInvoice(filename);
                    break;
                }
                case 6:
                    return 0;
                default:
                    std::cout << "Invalid option.\n";
                    break;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
