#ifndef FINALIZE_H
#define FINALIZE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <ctime>
#include "Admin.h" // Including AdminPanel header
#include "userW.h"
#include "customwer.h"
#include "payment.h"

using namespace std;

class Finalize : public Customer, public Payment
{
public:
    int choice;

    void finalize()
    {
        time_t now = time(0);
        char *dt = ctime(&now);
        
        do
        {
            cout << "Welcome To Our Online Shopping System" << endl;
            cout << "Please Enter Your Choice By numbers" << endl;
            cout << "1. Customer\n";
            cout << "2. Admin\n";
            cout << "3. View Products\n"; // Added option to view products
            cout << "4. About\n";
            cout << "5. Exit\n"; // Changed from 4 to 5
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1: 
                    User::getData();
                    Customer::working();
                    Customer::customerData();
                    if (done)
                    {
                        cout << endl;
                        cout << "Your Order Number is: " << OrderNumber << endl;
                        cout << endl;
                        cout << "Your Total Cost is: " << totalCost << "$" << endl;

                        cout << "Your Order will be delivered soon to you at address: " << address << endl;
                        cout << endl;
                        cout << "For any compliance call us on +923223132233." << endl;

                        cout << "Your Order Placed on local date and time: " << dt << endl;
                        cout << endl;

                        // writing the whole data into the file for record;
                        ofstream recordFile;
                        recordFile.open("RECORDS.txt", ios::app);

                        recordFile << "===================================================\n";
                        recordFile << "User: " << username << "\n";
                        recordFile << "User Record ID: " << number << "\n";
                        recordFile << "Order Number: " << OrderNumber << "\n";
                        recordFile << "\n";
                        recordFile << "Item\t\t"
                                   << "Price/Each\t\t"
                                   << "Total" << endl;
                        for (int i = 0; i < customerList.size(); i++)
                        {
                            for (int j = 0; j < 3; j++)
                            {
                                recordFile << customerList[i][j] << "\t\t";
                            }
                            recordFile << endl;
                        }
                        recordFile << endl;

                        recordFile << "Address: " << address << "\n";
                        recordFile << "Payment Method: " << paymentMethod << "\n";
                        recordFile << "The local date and time: " << dt << endl;
                        recordFile << "\n";

                        recordFile.close();
                    }
                    break;
                case 2:
                    adminPanel();
                    break;
                case 3:
                    viewProductsFromFile();
                    break;
                case 4:
                    About();
                    break;
                case 5:
                    cout << "Exiting..." << endl;
                    exit(0);
                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    break;
            }

            // If the choice is not to exit, ask if the user wants to choose again
            if (choice != 5)
            {
                char chooseAgain;
                cout << "Do you want to choose again? (y/n): ";
                cin >> chooseAgain;
                if (chooseAgain != 'y' && chooseAgain != 'Y')
                    break; // Break the loop if not choosing again
            }
        } while (choice != 5);
    }

    // Admin panel functionality
    void adminPanel()
    {
        AdminPanel adminPanel("admin", "admin123"); // Admin username and password
        adminPanel.adminControlPanel(); // Accessing admin control panel
    }

    void About()
    {
        cout << "About....." << endl;
    }

    // Function to view products from a file
    void viewProductsFromFile()
    {
        cout << "Viewing Products..." << endl;
        ifstream productsFile("products.txt");
        if (productsFile.is_open())
        {
            string productName;
            int count = 1;
            while (getline(productsFile, productName))
            {
                cout << count++ << ". " << productName << endl;
            }
            productsFile.close();
        }
        else
        {
            cout << "Unable to open products file." << endl;
        }
    }

    // Function to view users
    void viewUsers()
    {
        cout << "Viewing Users..." << endl;
        // Implement functionality to display users
        ifstream usersFile("users.txt");
        if (usersFile.is_open())
        {
            string line;
            while (getline(usersFile, line))
            {
                cout << line << endl;
            }
            usersFile.close();
        }
        else
        {
            cout << "Unable to open users file." << endl;
        }
    }
};

#endif // FINALIZE_H
