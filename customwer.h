#ifndef CUSTOMWER_H
#define CUSTOMWER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <ctime>

// file
#include "userW.h"
using namespace std;


class Customer : public User {
protected:
    bool ans = false;
    string contactNumber, address;

public:
    void working()
    {
        while (!ans)
        {
            string addedString; // this contains username+password

            addedString = User::getData();

            if (checkData(addedString))
            {
                ans = true;
            }

            else
            {
                cout << "Your Account doesn't exist in out records,\nDo you want to CREATE ACCOUNT? Y/N: ";
                char select;
                cin >> select;
                if (select == 'y' || select == 'Y')
                {
                    User::createAccount(addedString);
                }
                else
                {
                    cout << "Thank for using our service!!" << endl;
                    ans = false;
                    break;
                }
                ans = true;
            }
        }
    }
    bool returnAuthorized()
    {
        return ans;
    }
    void customerData()
    {
        if (ans == true)
        {
            number += 1;
            cout << "Dear " << username << " , Please enter your Billing address: ";
            cin.ignore();
            getline(cin, this->address);
            cout << endl;
            cout << "Thank You for the moment!!" << endl
                 << "Your id is: " << number << endl;
            cout << endl;
        }
    }
};

#endif