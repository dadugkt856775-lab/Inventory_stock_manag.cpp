#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Product {
private:
    int productID;
    string productName;
    double price;
    int quantity;

public:
    Product(int id, string name, double p, int q) {
        productID = id;
        productName = name;
        price = p;
        quantity = q;
    }

    int getID() const {
        return productID;
    }

    int getQuantity() const {
        return quantity;
    }

    void display() const {
        cout << left << setw(10) << productID
             << setw(22) << productName
             << right << setw(10) << fixed
             << setprecision(2) << price
             << setw(10) << quantity
             << setw(14) << price * quantity
             << endl;
    }

    void addStock(int amount) {
        if (amount > 0) {
            quantity += amount;
            cout << "Stock updated successfully!\n";
        } else {
            cout << "Invalid quantity!\n";
        }
    }

    void sellProduct(int amount) {
        if (amount <= 0) {
            cout << "Enter a valid quantity!\n";
        } else if (amount > quantity) {
            cout << "Insufficient stock!\n";
        } else {
            quantity -= amount;
            cout << "Sale completed successfully!\n";
            cout << "Total sale amount: Rs. "
                 << fixed << setprecision(2)
                 << price * amount << endl;
        }
    }

    double inventoryValue() const {
        return price * quantity;
    }
};

class Inventory {
private:
    vector<Product> products;

public:
    void addProduct() {
        int id, quantity;
        string name;
        double price;

        cout << "Enter product ID: ";
        cin >> id;

        for (const Product& p : products) {
            if (p.getID() == id) {
                cout << "Product ID already exists!\n";
                return;
            }
        }

        cout << "Enter product name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Enter price: Rs. ";
        cin >> price;

        cout << "Enter initial quantity: ";
        cin >> quantity;

        if (price <= 0 || quantity < 0) {
            cout << "Invalid price or quantity!\n";
            return;
        }

        products.emplace_back(id, name, price, quantity);
        cout << "Product added successfully!\n";
    }

    void displayProducts() const {
        if (products.empty()) {
            cout << "Inventory is empty!\n";
            return;
        }

        cout << "\n========== INVENTORY REPORT ==========\n";
        cout << left << setw(10) << "ID"
             << setw(22) << "Product"
             << right << setw(10) << "Price"
             << setw(10) << "Quantity"
             << setw(14) << "Value" << endl;

        cout << string(66, '-') << endl;

        for (const Product& p : products) {
            p.display();
        }

        cout << string(66, '-') << endl;
    }

    void searchProduct() const {
        int id;
        cout << "Enter product ID: ";
        cin >> id;

        for (const Product& p : products) {
            if (p.getID() == id) {
                cout << "\nProduct found:\n";
                cout << left << setw(10) << "ID"
                     << setw(22) << "Product"
                     << right << setw(10) << "Price"
                     << setw(10) << "Quantity"
                     << setw(14) << "Value" << endl;
                p.display();
                return;
            }
        }

        cout << "Product not found!\n";
    }

    void updateStock() {
        int id, amount;

        cout << "Enter product ID: ";
        cin >> id;

        for (Product& p : products) {
            if (p.getID() == id) {
                cout << "Enter quantity to add: ";
                cin >> amount;
                p.addStock(amount);
                return;
            }
        }

        cout << "Product not found!\n";
    }

    void sellProduct() {
        int id, amount;

        cout << "Enter product ID: ";
        cin >> id;

        for (Product& p : products) {
            if (p.getID() == id) {
                cout << "Enter quantity to sell: ";
                cin >> amount;
                p.sellProduct(amount);
                return;
            }
        }

        cout << "Product not found!\n";
    }

    void calculateInventoryValue() const {
        double total = 0;

        for (const Product& p : products) {
            total += p.inventoryValue();
        }

        cout << fixed << setprecision(2);
        cout << "Total inventory value: Rs. "
             << total << endl;
    }
};

int main() {
    Inventory inventory;
    int choice;

    do {
        cout << "\n===== STOCK MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Product\n";
        cout << "2. Display Inventory\n";
        cout << "3. Search Product\n";
        cout << "4. Add Stock\n";
        cout << "5. Sell Product\n";
        cout << "6. Calculate Inventory Value\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            inventory.addProduct();
            break;

        case 2:
            inventory.displayProducts();
            break;

        case 3:
            inventory.searchProduct();
            break;

        case 4:
            inventory.updateStock();
            break;

        case 5:
            inventory.sellProduct();
            break;

        case 6:
            inventory.calculateInventoryValue();
            break;

        case 7:
            cout << "Exiting stock management system...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
