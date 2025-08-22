

// struct Item{
//     int serialNumber;
//     int quantity;
//     double price;
//     string name;
// };

// struct Coupon{
//     double cartValue;
//     double minDiscount;
//     double maxDiscount;
// };

// class ShoppingCart {
// private:
//     map<int, Item> inventory;  // Hash Map to store inventory items
//     unordered_map<int, int> cart;        // Hash Map to store cart items
//     priority_queue<double> discountHeap; // Heap to store available discounts
//     double cartTotal;

// public:
//     ShoppingCart() : cartTotal(0.0) {}

//     // Function to load inventory from a CSV file
//     void loadInventory(const string& filename) {
//         ifstream file(filename);
//         string line;

//         while (getline(file, line)) {
//             stringstream ss(line);
//             string token;
//             Item item;

//             getline(ss, token, ',');
//             item.serialNumber = stoi(token);
//             getline(ss, token, ',');
//             item.name = token;
//             getline(ss, token, ',');
//             item.quantity = stoi(token);
//             getline(ss, token, ',');
//             item.price = stod(token);

//             inventory[item.serialNumber] = item;
//         }
//     }

//     // Function to load discount coupons from a CSV file
//     void loadCoupons(const string& filename) {
//         ifstream file(filename);
//         string line;

//         while (getline(file, line)) {
//             stringstream ss(line);
//             string token;
//             Coupon coupon;

//             getline(ss, token, ',');
//             coupon.cartValue = stod(token);
//             getline(ss, token, ',');
//             coupon.minDiscount = stod(token);
//             getline(ss, token, ',');
//             coupon.maxDiscount = stod(token);

//             // Add max discount to the heap for later use
//             discountHeap.push(coupon.maxDiscount);
//         }
//     }

//     // Function to display all items available in the store
//     void displayStoreItems() {
//         cout << "\nAvailable Items in Store:\n";
//         cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
//         cout << setw(20) << "Serial"
//                   << setw(20) << "Name"
//                   << setw(20) << "Qty"
//                   << setw(30) << "Price\n";
//         cout << "------------------------------------------------------------------------------------------\n";
//         for (const auto& [serialNumber, item] : inventory) {
//             cout << setw(20) << item.serialNumber
//                       << setw(20) << item.name
//                       << setw(20) << item.quantity
//                       << setw(30) << item.price << "\n";
//         }
//         cout << "------------------------------------------------------------------------------------------\n\n";
//     }

//     // Function to add an item to the cart (writes to cart.csv)
//     void addItem(int serialNumber, int quantity) {
//         if (inventory.find(serialNumber) != inventory.end()) {
//             if (inventory[serialNumber].quantity >= quantity) {
//                 cartTotal += inventory[serialNumber].price * quantity;
//                 inventory[serialNumber].quantity -= quantity;

//                 // Write the item to the cart CSV file
//                 ofstream cartFile("cart.csv", ios::app);
//                 if (cartFile.is_open()) {
//                     cartFile << serialNumber << "," 
//                              << inventory[serialNumber].name << "," 
//                              << quantity << "," 
//                              << inventory[serialNumber].price << "\n";
//                     cartFile.close();
//                 }
//                 cout << "Added " << quantity << " x " << inventory[serialNumber].name << " to the cart.\n";
//             } else {
//                 cout << "Insufficient quantity in store. Only " << inventory[serialNumber].quantity << " available.\n";
//             }
//         } else {
//             cout << "Item with serial number " << serialNumber << " does not exist.\n";
//         }
//     }

//     // Helper function to reload cart into a map from cart.csv
//     unordered_map<int, int> loadCartFromFile() {
//         unordered_map<int, int> cart;
//         ifstream cartFile("cart.csv");
//         string line;

//         while (getline(cartFile, line)) {
//             stringstream ss(line);
//             string token;
//             int serialNumber, quantity;

//             getline(ss, token, ',');
//             serialNumber = stoi(token);
//             getline(ss, token, ','); // skip name
//             getline(ss, token, ',');
//             quantity = stoi(token);

//             cart[serialNumber] += quantity;
//         }
//         cartFile.close();
//         return cart;
//     }

//     // Function to remove an item from the cart (updates cart.csv and adds back to store)
//     void removeItem(int serialNumber, int quantity) {
//         auto cart = loadCartFromFile();
//         if (cart.find(serialNumber) != cart.end()) {
//             if (cart[serialNumber] >= quantity) {
//                 cart[serialNumber] -= quantity;
//                 cartTotal -= inventory[serialNumber].price * quantity;
//                 inventory[serialNumber].quantity += quantity;  // Add back to inventory

//                 // Rewrite the cart.csv file after removing/updating the item
//                 ofstream cartFile("cart.csv");
//                 for (const auto& [serial, qty] : cart) {
//                     if (qty > 0) {
//                         cartFile << serial << "," << inventory[serial].name << "," 
//                                  << qty << "," << inventory[serial].price << "\n";
//                     }
//                 }
//                 cartFile.close();
//                 cout << "Removed " << quantity << " x " << inventory[serialNumber].name << " from the cart.\n";
//                 cout << "Added back to the store inventory.\n";

//             } else {
//                 cout << "You only have " << cart[serialNumber] << " in your cart.\n";
//             }
//         } else {
//             cout << "Item not in cart.\n";
//         }
//     }

//     /*
    
//     // Function to add an item to the cart
//     void addItem(int serialNumber, int quantity) {
//         if (inventory.find(serialNumber) != inventory.end() && inventory[serialNumber].quantity >= quantity) {
//             cart[serialNumber] += quantity;
//             cartTotal += inventory[serialNumber].price * quantity;
//             inventory[serialNumber].quantity -= quantity;
//             cout << "Added " << quantity << " x " << inventory[serialNumber].name << " to the cart.\n";
//         } else {
//             cout << "Required Quantity/Item not available. \n";
//         }
//     }

//     // Function to remove an item from the cart
//     void removeItem(int serialNumber, int quantity) {
//         if (cart.find(serialNumber) != cart.end() && cart[serialNumber] >= quantity) {
//             cart[serialNumber] -= quantity;
//             cartTotal -= inventory[serialNumber].price * quantity;
//             inventory[serialNumber].quantity += quantity;  // Return the item to inventory
//             cout << "Removed " << quantity << " x " << inventory[serialNumber].name << " from the cart.\n";

//             // If the item quantity in the cart becomes zero, remove it from the cart
//             if (cart[serialNumber] == 0) {
//                 cart.erase(serialNumber);
//             }
//         } 
//         else {
//             cout << "Item not in cart or insufficient quantity to remove.\n";
//         }
//     }
//     // Function to display cart details
//     void displayCart() {
//         cout << "Cart Contents:\n";
//         for (const auto& [serialNumber, quantity] : cart) {
//             const Item& item = inventory[serialNumber];
//             cout << item.name << " (Qty: " << quantity << ") - "
//                       << "Unit Price: ₹" << item.price << ", Total: ₹" << fixed << setprecision(2)
//                       << item.price * quantity << "\n";
//         }
//         cout << "Cart Total: ₹" << fixed << setprecision(2) << cartTotal << "\n";
//     }
//     */

//    // Function to display cart details by reading from cart.csv
//     void displayCart() {
//         ifstream cartFile("cart.csv");
//         string line;
//         double total = 0.0;

//         cout << "Cart Contents:\n";
//         cout << "---------------------------------------------\n";
//         cout << setw(10) << "Serial"
//                   << setw(30) << "Name"
//                   << setw(10) << "Qty"
//                   << setw(10) << "Price\n";
//         cout << "---------------------------------------------\n";

//         while (getline(cartFile, line)) {
//             stringstream ss(line);
//             string token;
//             int serialNumber, quantity;
//             double price;
//             string name;

//             getline(ss, token, ',');
//             serialNumber = stoi(token);
//             getline(ss, token, ',');
//             name = token;
//             getline(ss, token, ',');
//             quantity = stoi(token);
//             getline(ss, token, ',');
//             price = stod(token);

//             cout << setw(10) << serialNumber
//                       << setw(15) << name
//                       << setw(10) << quantity
//                       << setw(10) << price << "\n";
//             total += price * quantity;
//         }
//         cartFile.close();
//         cout << "---------------------------------------------\n";
//         cout << "Cart Total: ₹" << fixed << setprecision(2) << total << "\n";
//     }


//     // Function to apply the best discount
//     void applyBestDiscount() {
//         if (!discountHeap.empty() && cartTotal >= discountHeap.top()) {
//             double discount = discountHeap.top();
//             cartTotal -= discount;
//             cout << "Applied discount of ₹" << discount << ". New Total: ₹" << fixed << setprecision(2)
//                       << cartTotal << "\n";
//         } else {
//             cout << "No applicable discount.\n";
//         }
//     }

//     // Function to checkout
//     void checkout() {
//         displayCart();
//         applyBestDiscount();
//         cout << "Checkout complete. Please pay ₹" << fixed << setprecision(2) << cartTotal << ".\n";
//     }

//     // Function to handle user choices
//     void userInteraction() {
//         int choice;
//         do {
//             // displayStoreItems();
//             cout << "\nSelect an option:\n";
//             cout << "1. Add Item to Cart\n";
//             cout << "2. Remove Item from Cart\n";
//             cout << "3. View Cart\n";
//             cout << "4. Checkout\n";
//             cout << "Enter your choice: ";
//             cin >> choice;


//             switch (choice) {
//                 case 1: {
//                     int serial, quantity;
//                     displayStoreItems();
//                     cout << "Enter the serial number of the item to add: ";
//                     cin >> serial;
//                     cout << "Enter the quantity to add: ";
//                     cin >> quantity;
//                     addItem(serial, quantity);
//                     break;
//                 }
//                 case 2: {
//                     int serial, quantity;
//                     displayCart();
//                     cout << "Enter the serial number of the item to remove: ";
//                     cin >> serial;
//                     cout << "Enter the quantity to remove: ";
//                     cin >> quantity;
//                     removeItem(serial, quantity);
//                     break;
//                 }
//                 case 3:
//                     displayCart();
//                     break;
//                 case 4:
//                     checkout();
//                     cout << "Thank you for shopping!\n";
//                     break;
//                 default:
//                     cout << "Invalid choice. Please try again.\n";
//                     break;
//             }
//         } while (choice != 5);
//     }
// };