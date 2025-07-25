
README — Beverage Shop Billing System (C++ Project)
==================================================

Project Title:
--------------
Billing System for a Beverage Shop (C++ Console Application)

Description:
------------
This is a simple object-oriented billing system designed for small beverage shops.
It automates beverage selection, bill generation, and stores the bill into a file.

Features:
---------
- Object-Oriented Design using:
  - Classes & Objects
  - Inheritance (Product → Beverage)
  - Encapsulation
  - Constructor & Destructor
  - File Handling (save bills to bill.txt)
- Console Menu
- Calculates total, tax, and discount

Technologies Used:
------------------
- Language: C++
- Compiler: Dev-C++, VS-code.

Files Included:
---------------
- main.cpp        → Main source code file
- bill.txt        → Auto-generated file storing saved bills

How to Compile and Run:
------------------------
1. Open your C++ terminal.
2. Create a new file called 'main.cpp' and paste the program code into it.
3. Compile using terminal :
   - In terminal: `g++ main.cpp -o billing`
4. Run the program:
   - In terminal: `./billing`
5. Follow the on-screen instructions to enter customer and billing info.

Sample Output:
--------------
Enter Customer Name: Bishon Lamichane
Enter Phone Number: 9841xxxxxx

Available Beverages:
ID   Name           Price     Flavor    Size
1    Coke           80        Classic   Small
2    Lassi          70        Orange    Medium
3    Cold Coffee    100       Mocha     Large
4    Hot Coffee     80        Mocha     Medium
5    Black Tea      20        Mocha     Small
6    Milk Tea       30        Green     Medium

Enter Beverage ID to add to bill (0 to finish): 1
Enter quantity: 2

Total : 130.00

Notes:
------
- No STL vector used for maximum compiler compatibility.
- All bills are saved in 'bill.txt'.
