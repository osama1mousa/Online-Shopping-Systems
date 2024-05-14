#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class AdminPanel
{
private:
    string adminUsername;
    string adminPassword;

public:
    AdminPanel(string username, string password) : adminUsername(username), adminPassword(password) {}

    bool authenticate(string username, string password)
    {
        return (adminUsername == username && adminPassword == password);
    }

    void displayFunctions()
    {
        cout << "Welcome to the Admin Panel" << endl;
        cout << "1. View Records" << endl;
        cout << "2. View Users" << endl;
        cout << "3. Add Product" << endl;
        cout << "4. Delete Product" << endl;
        cout << "5. View Products" << endl;
        cout << "6. Exit" << endl;
    }

    void viewRecords()
    {
        cout << "Viewing Records..." << endl;
        // Implement viewing records functionality here
        ifstream recordsFile("records.txt");
        if (recordsFile.is_open())
        {
            string line;
            while (getline(recordsFile, line))
            {
                cout << line << endl;
            }
            recordsFile.close();
        }
        else
        {
            cout << "Unable to open records file." << endl;
        }
    }

    void viewUsers()
    {
        cout << "Viewing Users..." << endl;
        // Implement viewing users functionality here
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

    void addProduct()
    {
        cout << "Adding Product..." << endl;
        // Implement adding product functionality here
        string productName;
        cout << "Enter product name: ";
        cin >> productName;
        ofstream productsFile("products.txt", ios::app);
        if (productsFile.is_open())
        {
            productsFile << productName << endl;
            cout << "Product added successfully." << endl;
            productsFile.close();
        }
        else
        {
            cout << "Unable to open products file." << endl;
        }
    }

    void deleteProduct()
    {
        cout << "Deleting Product..." << endl;
        // Implement deleting product functionality here
        string productName;
        cout << "Enter product name to delete: ";
        cin >> productName;
        ifstream inputFile("products.txt");
        ofstream outputFile("temp.txt");
        bool found = false;
        if (inputFile.is_open() && outputFile.is_open())
        {
            string line;
            while (getline(inputFile, line))
            {
                if (line != productName)
                {
                    outputFile << line << endl;
                }
                else
                {
                    found = true;
                }
            }
            inputFile.close();
            outputFile.close();
            remove("products.txt");
            rename("temp.txt", "products.txt");
        }
        else
        {
            cout << "Unable to open products file." << endl;
        }
        if (found)
        {
            cout << "Product deleted successfully." << endl;
        }
        else
        {
            cout << "Product not found." << endl;
        }
    }

    void viewProducts()
    {
        cout << "Viewing Products..." << endl;
        // Implement viewing products functionality here
        ifstream productsFile("products.txt");
        if (productsFile.is_open())
        {
            string line;
            int count = 0;
            while (getline(productsFile, line))
            {
                cout << ++count << ". " << line << endl;
            }
            productsFile.close();
        }
        else
        {
            cout << "Unable to open products file." << endl;
        }
    }

    void adminControlPanel()
    {
        string username, password;
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        cin >> password;

        if (authenticate(username, password))
        {
            int adminChoice;
            do
            {
                displayFunctions();
                cout << "Enter your choice: ";
                cin >> adminChoice;

                switch (adminChoice)
                {
                    case 1:
                        viewRecords();
                        break;
                    case 2:
                        viewUsers();
                        break;
                    case 3:
                        addProduct();
                        break;
                    case 4:
                        deleteProduct();
                        break;
                    case 5:
                        viewProducts();
                        break;
                    case 6:
                        cout << "Exiting Admin Panel" << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please enter a valid option." << endl;
                        break;
                }
                
                // Ask if admin wants to choose again
                if (adminChoice != 6)
                {
                    char choice;
                    cout << "Do you want to choose again? (y/n): ";
                    cin >> choice;
                    if (choice != 'y' && choice != 'Y')
                        break;
                }
            } while (adminChoice != 6);
        }
        else
        {
            cout << "Authentication failed. Invalid username or password." << endl;
        }
    }
};

#endif // ADMINPANEL_H
