# Sampoorna Shopping Cart with Discounts

## Project Description

*Sampoorna Shopping Cart with Discounts* is an online shopping cart system designed to manage inventory, promotions, and checkout efficiently. Using data structures such as hash maps, heaps, and arrays, the system supports item additions and removals from the cart, real-time inventory updates, and application of optimal discounts for a smooth shopping experience.

## Features

- **Inventory Management**: Load items from a CSV file and manage stock levels.
- **Promotion Management**: Handle multiple discount coupons, applying the best available discount based on cart total.
- **Cart Operations**: Add and remove items, automatically updating quantities and tracking all changes in `cart.csv`.
- **Checkout and Discounts**: Apply discounts at checkout and clear cart items post-purchase.

## Technologies Used

- **C++ Standard Libraries**: Data structures and file handling.
- **CSV Parsing**: Load items and coupons from CSV files.
- **File I/O**: Store cart details in a CSV file for session continuity.

## Project Structure

- `project.cpp`: Contains the main C++ code for the shopping cart system.
- `items.csv`: Lists available store items with details (serial number, name, quantity, price).
- `coupons.csv`: Contains discount coupons (cart value, minimum discount, maximum discount).
- `cart.csv`: Tracks cart contents in real-time as items are added or removed.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., `g++`)

### Installation

1. **Clone the repository**:
   ```sh
   git clone https://github.com/your_username/Sampoorna-Shopping-Cart.git
   cd Sampoorna-Shopping-Cart
