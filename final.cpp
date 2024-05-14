#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int totalproducts = 0;
double totalPrice = 0;
map<int, double> discounts;

class Product {
public:
    int id;
    string name;
    double price;
    string quantity;

    Product(int id, string name, double price, string quantity)
        : id(id), name(name), price(price), quantity(quantity) {}
};

class User {
    string nickname;
    string password;
    double balance = 0;
    string attempt;

public:
    string username;
    bool returns = true;

    User() {
        cout << "\n\t\t\tWelcome to EazyMart!!!" << endl;
        cout << "\t\tPlease create an Account to continue Shopping" << endl;
        cout << "Enter Your username: ";
        getline(cin, username);
        cout << "Enter Your Password: ";
        getline(cin, password);
        cout << "Enter a nickname(This will be used to reset password): ";
        getline(cin, nickname);
        cout << "Add some balance to buy products:  ";
        cin >> balance;
        cin.ignore();
    }

    void checkout() {
        string checkpass;
    trypassagain:
        cout << endl << "Enter your password to confirm Checkout or (Type 0 to return Main Menu): ";
        getline(cin, checkpass);
        if (checkpass == "0") {
            returns = false;
        } else if (checkpass == password) {
            if (balance < totalPrice) {
                cout << "\nInsufficient Balance!!" << endl;
                cout << "Please add balance from (My Account and balance)" << endl << endl;
                returns = false;
            } else {
                double discountPercentage;
                cout << "Do you have a percentage discount to apply? (Enter 0 if none): ";
                cin >> discountPercentage;
                cin.ignore();
                if (discountPercentage > 0) {
                    totalPrice -= (totalPrice * discountPercentage) / 100;
                }
                balance -= totalPrice;
                cout << "\n\n\t\t-------------------------------------------" << endl;
                cout << "\t\t\t    Purchase Successful !!! " << endl;
                cout << "\t\t     Your current balance is " << balance << " Turkish Lira" << endl;
                cout << "\t\t-------------------------------------------\n\n\n" << endl;
                cout << "\t\t******************************************* ";
                cout << endl << "\t\t* Thank You For shopping with EazyMart!!! *" << endl;
                cout << "\t\t*      Hope you Have a lovely day!!!      *" << endl;
                cout << "\t\t*******************************************\n\n\n" << endl;
                returns = true;
            }
        } else {
            cout << endl << "Wrong Password!!! " << endl;
            cout << "If forgot password Please go My Account and Balance to Reset Password " << endl;
            goto trypassagain;
        }
    }

    void showBalance() const {
        cout << "\n\t\t\t  Your balance is " << balance << " Turkish Lira" << endl;
        cout << "\t\t-----------------------------------------" << endl;
    }

    void addBalance() {
        int extraBalance;
        cout << "Enter amount to add: ";
        cin >> extraBalance;
        balance += extraBalance;
        cout << "\t\t\t " << extraBalance << " Turkish Lira added successfully " << endl;
        cout << "\t\t\tCurrent Balance is " << balance << " Turkish Lira" << endl;
        cout << "\t\t-----------------------------------------" << endl;
    }

    void displayUserData() {
    attemptagain:
        cout << "Enter Your password: ";
        getline(cin, attempt);
        if (attempt == password) {
            cout << "\n\t\t\tYour UserName is " << username << endl;
            cout << "\t\t\tYour nickname is " << nickname << endl;
            cout << "\t\t\tYour Balance is " << balance << " Turkish Lira" << endl;
            cout << "\t\t-----------------------------------------" << endl;
        } else {
            cout << "Wrong password!!! Try Again!!!" << endl;
            goto attemptagain;
        }
    }

    void forgetPassword() {
        string forgetNick;
    forgetNickname:
        cout << "Enter your nickname: ";
        getline(cin, forgetNick);
        if (forgetNick == nickname) {
            cout << "Enter your new Password: ";
            getline(cin, password);
            cout << "Password reset Successful....." << endl;
        } else {
            cout << "Wrong Nickname!!! Try Again!!!" << endl;
            goto forgetNickname;
        }
    }
};

class Admin {
    string adminUsername = "admin";
    string adminPassword = "admin123";

public:
    vector<User> users;
    vector<Product> products;

    bool login() {
        string username, password;
        cout << "Enter Admin Username: ";
        getline(cin, username);
        cout << "Enter Admin Password: ";
        getline(cin, password);
        if (username == adminUsername && password == adminPassword) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Login failed!" << endl;
            return false;
        }
    }

    void addProduct() {
        int id;
        string name;
        double price;
        string quantity;
        cout << "Enter Product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Product Name: ";
        getline(cin, name);
        cout << "Enter Product Price: ";
        cin >> price;
        cin.ignore();
        cout << "Enter Product Quantity: ";
        getline(cin, quantity);
        products.push_back(Product(id, name, price, quantity));
        cout << "Product added successfully!" << endl;
    }

    void deleteProduct() {
        int productId;
        cout << "Enter Product ID to delete: ";
        cin >> productId;
        cin.ignore();
        products.erase(
            remove_if(products.begin(), products.end(), [&](Product &p) { return p.id == productId; }),
            products.end()
        );
        cout << "Product deleted successfully!" << endl;
    }

    void addUser() {
        User newUser;
        users.push_back(newUser);
        cout << "User added successfully!" << endl;
    }

    void viewUsers() const {
        cout << "\n\nList of Users:\n" << endl;
        for (const auto &u : users) {
            cout << "Username: " << u.username << endl;
        }
    }

    void viewProducts() const {
        cout << "\n\nList of Products:\n" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "ID     Name               Price        Quantity" << endl;
        cout << "-----------------------------------------------------------" << endl;
        for (const auto &p : products) {
            cout << p.id << "\t    " << p.name << "\t" << p.price << " Turkish Lira " << "\t" << p.quantity << endl;
        }
        cout << "-----------------------------------------------------------" << endl;
    }

    void setDiscount() {
        int productId;
        double discount;
        cout << "Enter Product ID to set discount: ";
        cin >> productId;
        cout << "Enter discount percentage (e.g., 10 for 10%): ";
        cin >> discount;
        discounts[productId] = discount;
        cout << "Discount set successfully!" << endl;
    }
};

class Shop {
    vector<string> cartedItems;
    vector<int> cartedQuantity;
    vector<double> cartedPrice;

public:
    void addCart(string item, int quantity, double price) {
        cartedItems.push_back(item);
        cartedQuantity.push_back(quantity);
        cartedPrice.push_back(price);
        cout << item << " Added to the cart!!!" << endl;
    }

    void displayCart() const {
        cout << "\n\nItems in the cart:\n" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Quantity      Name                               Price" << endl;
        cout << "-----------------------------------------------------------" << endl;
        for (size_t i = 0; i < cartedItems.size(); ++i) {
            cout << "  " << cartedQuantity[i];
            cout << "\t     " << cartedItems[i];
            cout << "\t     \t\t" << cartedPrice[i] << " Turkish Lira " << endl;
        }
        cout << endl << "-----------------------------------------------------------" << endl;
        cout << "\tTotal price is: \t\t\t" << totalPrice << " Turkish Lira" << endl;
    }
};

void displayProducts(const vector<Product> &products) {
    cout << "-----------------------------------------------------------" << endl;
    cout << "ProductID     Name               Price        Quantity" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (const auto &p : products) {
        cout << "  " << p.id;
        cout << "\t     " << p.name;
        cout << "\t" << p.price << " Turkish Lira ";
        cout << "\t" << p.quantity << endl;
    }
    cout << "-----------------------------------------------------------" << endl;
}

void handleProductChoice(Shop &shop, vector<Product> &products) {
    int choice, quantity;
    cout << "Enter a Product ID: ";
    cin >> choice;
    cout << "Enter quantity: ";
    cin >> quantity;

    for (auto &p : products) {
        if (p.id == choice) {
            double finalPrice = p.price;
            if (discounts.find(choice) != discounts.end()) {
                finalPrice -= (finalPrice * discounts[choice]) / 100;
            }
            shop.addCart(p.name, quantity, finalPrice * quantity);
            totalPrice += finalPrice * quantity;
            cout << "\nCurrent total is " << totalPrice << " Turkish Lira" << endl;
            cout << "***************************" << endl;
            totalproducts++;
            break;
        }
    }
}

int main() {
    vector<Product> products;
    Admin admin;

    while (true) {
        int option = 0;
        cout << "\n\t\t\t     Welcome to EazyMart!!!" << endl;
        cout << "\t\t\t  Are you a customer or an admin?" << endl;
        cout << "1. Customer" << endl;
        cout << "2. Admin" << endl;
        cout << "Enter an option: ";
        cin >> option;
        cin.ignore();

        if (option == 1) {
            User user;
            Shop shop;
            while (true) {
                cout << "\n\t\t\t     Welcome to EazyMart!!!" << endl;
                cout << "\t\t\t  What would you like to buy?" << endl << endl;
                cout << "1. View Products" << endl;
                cout << "2. My Account and Balance" << endl;
                cout << "3. Show my carted Products and Checkout" << endl;
                cout << "Enter an option: ";
                cin >> option;
                cin.ignore();

                switch (option) {
                    case 1:
                        displayProducts(products);
                        handleProductChoice(shop, products);
                        break;
                    case 2:
                        int userChoice;
                        cout << endl << "1. Check Balance " << endl;
                        cout << "2. Add More Balance " << endl;
                        cout << "3. Show my all data " << endl;
                        cout << "4. Reset password " << endl;
                        cout << "5. Return to Main Menu " << endl;
                        cin >> userChoice;
                        cin.ignore();
                        if (userChoice == 1)
                            user.showBalance();
                        else if (userChoice == 2)
                            user.addBalance();
                        else if (userChoice == 3)
                            user.displayUserData();
                        else if (userChoice == 4)
                            user.forgetPassword();
                        break;
                    case 3:
                        shop.displayCart();
                        user.checkout();
                        if (!user.returns) continue;
                        else exit(0);
                    default:
                        cout << "Invalid Option!!!" << endl;
                }
            }
        } else if (option == 2) {
            if (!admin.login()) continue;
            while (true) {
                cout << "\n\t\t\tAdmin Panel" << endl;
                cout << "1. Add Product" << endl;
                cout << "2. Delete Product" << endl;
                cout << "3. Add User" << endl;
                cout << "4. View Users" << endl;
                cout << "5. View Products" << endl;
                cout << "6. Set Discount" << endl;
                cout << "7. Return to Main Menu" << endl;
                cout << "Enter an option: ";
                cin >> option;
                cin.ignore();

                if (option == 7) {
                    break; // Exit to main menu
                }

                switch (option) {
                    case 1:
                        admin.addProduct();
                        products = admin.products;
                        break;
                    case 2:
                        admin.deleteProduct();
                        products = admin.products;
                        break;
                    case 3:
                        admin.addUser();
                        break;
                    case 4:
                        admin.viewUsers();
                        break;
                    case 5:
                        admin.viewProducts();
                        break;
                    case 6:
                        admin.setDiscount();
                        break;
                    default:
                        cout << "Invalid Choice!!!" << endl;
                }
            }
        } else {
            cout << "Invalid Option!!!" << endl;
        }
    }

    return 0;
}
