#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Structure to represent a product
struct Product {
    string name;
    string category;
    double price;
    double rating; // Average user rating (0.0 to 5.0)
    int stock; // Quantity in stock

    // Constructor
    Product(string _name, string _category, double _price, double _rating, int _stock) :
        name(_name), category(_category), price(_price), rating(_rating), stock(_stock) {}
};

// Function to print product details
void printProduct(const Product& product) {
    cout << "Name: " << product.name << endl;
    cout << "Category: " << product.category << endl;
    cout << "Price: $" << product.price << endl;
    cout << "Rating: " << product.rating << endl;
    cout << "Stock: " << product.stock << endl << endl;
}

// Function to add a product to the shopping cart
void addToCart(Product& product, int quantity, vector<Product>& cart) {
    if (product.stock >= quantity) {
        product.stock -= quantity;
        cart.push_back(product);
        cout << quantity << " " << product.name << "(s) added to the cart." << endl;
    } else {
        cout << "Insufficient stock!" << endl;
    }
}

// Function to display the contents of the shopping cart
void displayCart(const vector<Product>& cart) {
    if (cart.empty()) {
        cout << "Your cart is empty." << endl;
    } else {
        cout << "Items in your cart:" << endl;
        for (const Product& product : cart) {
            printProduct(product);
        }
    }
}

int main() {
    // Sample product database (replace with actual data source)
    vector<Product> products = {
        Product("Laptop X", "Electronics", 899.99, 4.5, 5),
        Product("Book Y", "Books", 19.99, 4.8, 10),
        Product("Headphones Z", "Electronics", 79.99, 4.2, 8),
        Product("Shirt A", "Clothing", 24.99, 4.0, 15),
    };

    // Hash table to store products by category (key) for efficient retrieval
    unordered_map<string, vector<Product>> productByCategory;

    // Add products to hash table by category
    for (const Product& product : products) {
        productByCategory[product.category].push_back(product);
    }

    // User interaction loop
    vector<Product> cart;
    while (true) {
        cout << "\n** Online Shopping Recommendation System **\n";
        cout << "1. Sort products by price (ascending)\n";
        cout << "2. Sort products by rating (descending)\n";
        cout << "3. Browse products by category\n";
        cout << "4. View and manage shopping cart\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // Sort products by price (ascending)
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
                return a.price < b.price;
            });
            cout << "\nProducts sorted by price (ascending):\n";
            for (const Product& product : products) {
                printProduct(product);
            }
        } else if (choice == 2) {
            // Sort products by rating (descending)
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
                return a.rating > b.rating;
            });
            cout << "\nProducts sorted by rating (descending):\n";
            for (const Product& product : products) {
                printProduct(product);
            }
        } else if (choice == 3) {
            cout << "\nEnter category to browse (or 'all' for all categories): ";
            string category;
            cin >> category;

            if (category == "all") {
                cout << "\nAll products:\n";
                for (const Product& product : products) {
                    printProduct(product);
                }
            } else {
                // Check if category exists in hash table
                if (productByCategory.count(category) > 0) {
                    cout << "\nProducts in category " << category << ":\n";
                    for (const Product& product : productByCategory[category]) {
                        printProduct(product);
                    }
                } else {
                    cout << "Category not found.\n";
                }
            }
        } else if (choice == 4) {
            // View and manage shopping cart
            cout << "\n** Shopping Cart **\n";
            cout << "1. View cart\n";
            cout << "2. Add item to cart\n";
            cout << "3. Remove item from cart\n";
            cout << "4. Checkout\n";
            cout << "Enter your choice: ";

            int cartChoice;
            cin >> cartChoice;

            if (cartChoice == 1) {
                displayCart(cart);
            } else if (cartChoice == 2) {
                cout << "Enter the name of the product: ";
                string productName;
                cin.ignore(); // Ignore previous newline character
                getline(cin, productName);

                cout << "Enter the quantity: ";
                int quantity;
                cin >> quantity;

                auto it = find_if(products.begin(), products.end(), [&productName](const Product& product) {
                    return product.name == productName;
                });

                if (it != products.end()) {
                    addToCart(*it, quantity, cart);
                } else {
                    cout << "Product not found." << endl;
                }
            } else if (cartChoice == 3) {
                cout << "Enter the name of the product to remove: ";
                string productName;
                cin.ignore(); // Ignore previous newline character
                getline(cin, productName);

                auto it = find_if(cart.begin(), cart.end(), [&productName](const Product& product) {
                    return product.name == productName;
                });

                if (it != cart.end()) {
                    it->stock++; // Increment stock when removing from cart
                    cart.erase(it);
                    cout << "Product removed from cart." << endl;
                } else {
                    cout << "Product not found in cart." << endl;
                }
            } else if (cartChoice == 4) {
                // Checkout
                double total = 0;
                for (const Product& product : cart) {
                    total += product.price;
                }
                cout << "Total amount: $" << total << endl;
                cout << "Thank you for shopping with us!" << endl;
                break;
            } else {
                cout << "Invalid choice.\n";
            }
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}
    
