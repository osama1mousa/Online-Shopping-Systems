#ifndef PAYMENT_H
#define PAYMENT_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <ctime>

// Classes
#include "userW.h"
#include "customwer.h"
#include "finalize.h"
using namespace std;
class ShoppingCart
{
protected:
    vector<vector<string>> customerList;
    bool order = false;
    map<string, int> mymap;

public:
    int validation()
    {
        int x;
        while (!(cin >> x))
        {
            cout << "Enter valid number!!" << endl;
            cin.clear();
            cin.ignore(123, '\n');
        }
        return x;
    }
    ShoppingCart()
    {
        mymap["Grocery   "] = 7;
        mymap["Fast food"] = 5;
        mymap["Electronic"] = 15;
        mymap["HouseHolds"] = 20;
    }

    void showItems(string userId)
    {
        cout << "Dear Customer " << userId << ", Select your items from below: " << endl;

        for (auto const &pair : mymap)
        {
            vector<string> userls;
            int x;
            cout << "Package " << pair.first << " of Price " << pair.second << "$ EACH!" << endl;
            cout << "Enter Quantity for " << pair.first << ": ";
            x = validation();
            cout << endl;
            if (x != 0)
            {
                userls.push_back(pair.first);
                userls.push_back(to_string(pair.second));
                userls.push_back(to_string(pair.second * x));
                // customerList.push_back()
            }
            if (!userls.empty())
            {
                customerList.push_back(userls);
            }
        }
    }
};

class Payment : public ShoppingCart
{
protected:
    double totalCost = 0;
    bool done = false;
    static int OrderNumber;
    string paymentMethod;
    string card;
    string pin;

public:
    void showCosts()
    {

        cout << "Your Order Number is: " << OrderNumber << endl;
        cout << "Item\t\t"
             << "Price/Each\t\t"
             << "Total" << endl;

        for (int i = 0; i < customerList.size(); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << customerList[i][j] << "\t\t";
                if (j == 2)
                {
                    stringstream ss(customerList[i][j]);
                    int x = 0;
                    ss >> x;
                    totalCost += x;
                }
            }
            cout << endl;
        }
        cout << endl;
        cout << "YOUR TOTAL COST IS: " << totalCost << "$" << endl;
        cout << endl;
    }

    void agrii()
    {
        cout << "Do you want to continue to Payment step? Y/N: ";
        char y;
        cin >> y;
        if (y == 'Y' || y == 'y')
        {
            done = true;
            OrderNumber += 1;
            cout << "Please Enter your Payment Method 1 or 2" << endl;
            cout << "1: Cash On delivery" << endl;
            cout << "2: Credit Card" << endl;
            cout << endl;
            cout << "Your Method: ";
            int y;
            cin >> y;
            if (y == 1)
            {
                paymentMethod = "Cash On Delivery!";
            }
            else if (y == 2)
            {
                paymentMethod = "Credit Card";
                cout << "Enter Credit Card number: ";
                cin >> card;
                cout << "Enter Your PIN: ";
                cin >> pin;
            }
        }
        else
        {
            done = false;
            cout << "Thank you for using our Service!!" << endl;
        }
    }
};

int Payment::OrderNumber = rand() % 100 + 1000;

#endif