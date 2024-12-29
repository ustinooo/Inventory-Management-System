// Inventory Management System _ Olavario.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

// Item structure to represent each inventory item
struct Item {
    int id;
    string name;
    int quantity;
    double price;
};

// Function to display inventory
void displayInventory(const vector<Item>& inventory) {
    cout << "\nInventory List:\n";
    cout << "ID\tName\t\tQuantity\tPrice\n";
    for (const auto& item : inventory) {
        cout << item.id << "\t" << item.name << "\t\t" << item.quantity << "\t\t" << item.price << endl;
    }
}

// Function to search an item by name using Linear Search
Item* searchItemByName(vector<Item>& inventory, const string& name) {
    for (auto& item : inventory) {
        if (item.name == name) {
            return &item;
        }
    }
    return nullptr; // Item not found
}

// Function to add a new item to inventory
void addItem(vector<Item>& inventory, int id, const string& name, int quantity, double price) {
    Item newItem = { id, name, quantity, price };
    inventory.push_back(newItem);
}

// Function to delete an item by ID
void deleteItem(vector<Item>& inventory, int id) {
    auto it = find_if(inventory.begin(), inventory.end(), [id](const Item& item) { return item.id == id; });
    if (it != inventory.end()) {
        inventory.erase(it);
        cout << "Item with ID " << id << " deleted.\n";
    }
    else {
        cout << "Item not found.\n";
    }
}

// Function to update item quantity or price
void updateItem(vector<Item>& inventory, int id, int quantity, double price) {
    for (auto& item : inventory) {
        if (item.id == id) {
            item.quantity = quantity;
            item.price = price;
            cout << "Item with ID " << id << " updated.\n";
            return;
        }
    }
    cout << "Item not found.\n";
}

// Function to sort inventory by name (Bubble Sort)
void bubbleSortByName(vector<Item>& inventory) {
    for (size_t i = 0; i < inventory.size() - 1; ++i) {
        for (size_t j = 0; j < inventory.size() - i - 1; ++j) {
            if (inventory[j].name > inventory[j + 1].name) {
                swap(inventory[j], inventory[j + 1]);
            }
        }
    }
}

// Function to sort inventory by price (Quick Sort)
int partition(vector<Item>& inventory, int low, int high) {
    double pivot = inventory[high].price;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (inventory[j].price < pivot) {
            i++;
            swap(inventory[i], inventory[j]);
        }
    }
    swap(inventory[i + 1], inventory[high]);
    return i + 1;
}

void quickSortByPrice(vector<Item>& inventory, int low, int high) {
    if (low < high) {
        int pi = partition(inventory, low, high);
        quickSortByPrice(inventory, low, pi - 1);
        quickSortByPrice(inventory, pi + 1, high);
    }
}

int main() {
    vector<Item> inventory;
    unordered_map<int, Item> itemMap;
    int choice;

    while (true) {
        cout << "\nInventory Management System\n";
        cout << "1. Add Item\n";
        cout << "2. Delete Item\n";
        cout << "3. Update Item\n";
        cout << "4. Display Inventory\n";
        cout << "5. Search Item by Name\n";
        cout << "6. Sort Inventory by Name (Bubble Sort)\n";
        cout << "7. Sort Inventory by Price (Quick Sort)\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, quantity;
            string name;
            double price;
            cout << "Enter item ID: ";
            cin >> id;
            cout << "Enter item name: ";
            cin.ignore();  // Ignore any leftover newline
            getline(cin, name);
            cout << "Enter item quantity: ";
            cin >> quantity;
            cout << "Enter item price: ";
            cin >> price;
            addItem(inventory, id, name, quantity, price);
            itemMap[id] = inventory.back(); // Add to map for quick lookup
        }
        else if (choice == 2) {
            int id;
            cout << "Enter item ID to delete: ";
            cin >> id;
            deleteItem(inventory, id);
            itemMap.erase(id); // Remove from map
        }
        else if (choice == 3) {
            int id, quantity;
            double price;
            cout << "Enter item ID to update: ";
            cin >> id;
            cout << "Enter new quantity: ";
            cin >> quantity;
            cout << "Enter new price: ";
            cin >> price;
            updateItem(inventory, id, quantity, price);
            itemMap[id] = inventory.back(); // Update map
        }
        else if (choice == 4) {
            displayInventory(inventory);
        }
        else if (choice == 5) {
            string name;
            cout << "Enter item name to search: ";
            cin.ignore();
            getline(cin, name);
            Item* foundItem = searchItemByName(inventory, name);
            if (foundItem) {
                cout << "Item Found: ID = " << foundItem->id << ", Name = " << foundItem->name
                    << ", Quantity = " << foundItem->quantity << ", Price = " << foundItem->price << endl;
            }
            else {
                cout << "Item not found.\n";
            }
        }
        else if (choice == 6) {
            bubbleSortByName(inventory);
            cout << "Inventory sorted by name (Bubble Sort).\n";
        }
        else if (choice == 7) {
            quickSortByPrice(inventory, 0, inventory.size() - 1);
            cout << "Inventory sorted by price (Quick Sort).\n";
        }
        else if (choice == 8) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
