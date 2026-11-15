# Inventory Management System

A C++17 application developed as a personal project to manage products and inventory operations through a simple console interface.

## Overview

The application allows users to manage an inventory by adding, searching, updating and removing products. It also keeps track of product quantities and calculates the total value of the inventory.

Data is stored locally in a text file, so the inventory is available again when the application is restarted.

## Main Features

- Add new products with ID, name, price and quantity
- Display the current inventory
- Search for products by ID
- Update existing product information
- Remove products with confirmation
- Calculate individual and total inventory value
- Save and load inventory data automatically
- Validate user input and handle invalid entries

## Technologies

- **Language:** C++17
- **Data structures:** `struct`, `std::vector`
- **File handling:** `fstream`
- **Programming concepts:** Functions, loops, conditions, references and input validation
- **Tools:** GCC, Visual Studio Code, Git and GitHub

## Build and Run

Compile the project using GCC:

```bash
g++ main.cpp -std=c++17 -Wall -Wextra -o inventory.exe
```

Run on Windows:

```powershell
.\inventory.exe
```

On Linux/macOS:

```bash
./inventory
```

## Data Storage

The application uses a local file named `prodotti.txt` to store inventory information.

Product data is saved after changes and loaded automatically when the application starts.

## Future Improvements

Further development may include:
- Organizing the source code into separate header and implementation files
- Adding automated tests
- Introducing a database for data storage
- Expanding inventory management with categories and suppliers

