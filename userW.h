#ifndef USERW_H
#define USERW_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <ctime>
#include "Admin.h"
using namespace std;

// Base class for products
string encrypt(string, string);
string encrypt(string user, string pass)
{
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string us = "UserName=", ps = "Password=";
    for (char x : user)
    {   
        if (isalpha(x))
        {
            int y;
            y = letters.find(x);
            us += to_string(y * 2);
            us += "\\";
        }
        else
        {
            us += to_string(x);
            us += "\\";
        }
    }
    for (char x : pass)
    {
        if (isalpha(x))
        {
            int y;
            y = letters.find(x);
            ps += to_string(y * 2);
            ps += "/";
        }
        else
        {
            ps += to_string(x);
            ps += "/";
        }
    }
    return us + ps;
}

class User
{
protected:
    string username, password;
    string formatedString;
public:
    static int number;
    virtual string getData()
{
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;
            formatedString = encrypt(username, password);
            return formatedString;
        
    return ""; // return an empty string or handle the return value accordingly
}

    void createAccount(string userData)
    {
        ofstream cout; // object for writing into the file

        cout.open("Users.txt", ios::app); // opening the file in apppend mode

        cout << userData << "\n";

        cout << "Your Account has been Created" << endl;
        // number += 1;

        cout.close();
    }

    virtual bool checkData(string userData)
    {
        int offset;
        string line;
        ifstream Myfile;
        Myfile.open("Users.txt");

        if (Myfile.is_open())
        {
            while (!Myfile.eof())
            {
                getline(Myfile, line);
                if ((offset = line.find(userData, 0)) != string::npos)
                {
                    cout << "ACCOUNT FOUND" << endl;
                    return true;
                }
                else if (Myfile.eof())
                {
                    cout << "ACCOUNT NOT FOUND, PLEASE CREATE ACCOUNT!!" << endl;
                }
            }
            Myfile.close();
        }
        else
            cout << "Unable to open this file." << endl;

        return false;
    }
};

int User::number = rand() % 100 + 10000;

#endif // USER_H
