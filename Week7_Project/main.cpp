//********************************************************************
// Author: Luis Rios
// Assignment: Week7_Project
// Description: This program users enums, structs, and arrays to store
//              and display information about sneakers. It includes a
//              menu interface that allows the user to view and add
//              sneakers to the collection.
//********************************************************************


#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Enum for different sneaker brands
enum SneakerBrand { NIKE, ADIDAS, JORDAN, NEW_BALANCE, VANS, OTHER };

// Enum for sneaker categories
enum SneakerCategory { RUNNING, BASKETBALL, LIFESTYLE, SKATE, TRAINING };

// Struct to hold sneaker information
struct Sneaker {
    string modelName;
    SneakerBrand brand;
    SneakerCategory category;
    double size;
    double price;
    bool isDeadstock;
    int yearReleased;
};

// Turns the brand enum into a readable string
string brandToString(SneakerBrand b) {
    switch (b) {
        case NIKE:        return "Nike";
        case ADIDAS:      return "Adidas";
        case JORDAN:      return "Jordan";
        case NEW_BALANCE: return "New Balance";
        case VANS:        return "Vans";
        case OTHER:       return "Other";
        default:          return "Unknown";
    }
}

// Turns the category enum into a readable string
string categoryToString(SneakerCategory c) {
    switch (c) {
        case RUNNING:    return "Running";
        case BASKETBALL: return "Basketball";
        case LIFESTYLE:  return "Lifestyle";
        case SKATE:      return "Skate";
        case TRAINING:   return "Training";
        default:         return "Unknown";
    }
}

// Displays the details
void displaySneaker(Sneaker s) {
    cout << "Model Name   : " << s.modelName << "\n";
    cout << "Brand        : " << brandToString(s.brand) << "\n";
    cout << "Category     : " << categoryToString(s.category) << "\n";
    cout << "Size         : " << s.size << "\n";
    cout << "Price (USD)  : $" << fixed << setprecision(2) << s.price << "\n";
    cout << "Deadstock    : " << (s.isDeadstock ? "Yes" : "No") << "\n";
    cout << "Year Released: " << s.yearReleased << "\n";
}

// Displays all sneakers in the array
void displayAll(Sneaker arr[], int count) {
    if (count == 0) {
        cout << "No sneakers in the collection.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << "\n----- Sneaker #" << (i + 1) << " -----\n";
        displaySneaker(arr[i]);
    }
}

// Gets an integer from the user and makes sure it's valid
int readIntInRange(const string& prompt, int minVal, int maxVal) {
    int val;
    cout << prompt;
    while (!(cin >> val) || val < minVal || val > maxVal) {
        cout << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');
    return val;
}

// Gets a double value from the user

double readDouble(const string& prompt) {
    double val;
    cout << prompt;
    while (!(cin >> val)) {
        cout << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');
    return val;
}

// yes/no input for true or false values
bool readYesNo(const string& prompt) {
    char ch;
    cout << prompt << " (y/n): ";
    while (!(cin >> ch) || (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')) {
        cout << "Please enter y or n: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');
    return (ch == 'y' || ch == 'Y');
}

// Adds a new sneaker to the array
void addSneaker(Sneaker arr[], int& count, int maxSize) {
    if (count >= maxSize) {
        cout << "Collection is full. Cannot add more.\n";
        return;
    }

    Sneaker s;

    cout << "Enter model name: ";
    getline(cin, s.modelName);

    cout << "\nSelect a brand:\n";
    cout << "1. Nike\n2. Adidas\n3. Jordan\n4. New Balance\n5. Vans\n6. Other\n";
    int brandChoice = readIntInRange("Choice (1-6): ", 1, 6);
    s.brand = static_cast<SneakerBrand>(brandChoice - 1);

    cout << "\nSelect a category:\n";
    cout << "1. Running\n2. Basketball\n3. Lifestyle\n4. Skate\n5. Training\n";
    int catChoice = readIntInRange("Choice (1-5): ", 1, 5);
    s.category = static_cast<SneakerCategory>(catChoice - 1);

    s.size = readDouble("Enter size: ");
    s.price = readDouble("Enter retail price in USD: ");
    s.isDeadstock = readYesNo("Is it deadstock (unworn/in box)?");
    s.yearReleased = readIntInRange("Enter year released: ", 1900, 2100);

    arr[count] = s;
    count++;

    cout << "Sneaker added!\n";
}

int main() {
    const int MAX_SNEAKERS = 20;
    Sneaker collection[MAX_SNEAKERS];
    int count = 8;

    // Starter sneakers for testing
    collection[0] = {"Air Runner", NIKE, RUNNING, 10.5, 120.00, false, 2020};
    collection[1] = {"Street Flex", ADIDAS, LIFESTYLE, 10.0, 95.00, true, 2019};
    collection[2] = {"Court Pro", JORDAN, BASKETBALL, 11.0, 150.00, false, 2018};
    collection[3] = {"Everyday Comfort", NEW_BALANCE, LIFESTYLE, 9.5, 110.00, false, 2021};
    collection[4] = {"Skate Classic", VANS, SKATE, 10.0, 75.00, true, 2017};
    collection[5] = {"Trainer X", NIKE, TRAINING, 10.5, 130.00, false, 2022};
    collection[6] = {"Hoops Max", ADIDAS, BASKETBALL, 11.5, 140.00, false, 2020};
    collection[7] = {"Casual Low", OTHER, LIFESTYLE, 10.0, 60.00, false, 2016};

    int choice;
    do {
        cout << "\n===== Sneaker Collection Manager =====\n";
        cout << "1. Display All Sneakers\n";
        cout << "2. Add a Sneaker\n";
        cout << "3. Search by Brand       [Part 2]\n";
        cout << "4. Search by Size        [Part 2]\n";
        cout << "5. Sort by Price         [Part 2]\n";
        cout << "6. Sort by Year          [Part 2]\n";
        cout << "0. Exit\n";

        choice = readIntInRange("Enter choice: ", 0, 6);

        switch (choice) {
            case 1:
                displayAll(collection, count);
                break;
            case 2:
                addSneaker(collection, count, MAX_SNEAKERS);
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                cout << "Coming in Part 2...\n";
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
        }
    } while (choice != 0);

    return 0;
}