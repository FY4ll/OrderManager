# OrderManager

OrderManager is a cross-platform desktop application developed in **C++17** with **Qt 6**.

The project is built progressively through several functional versions. Each version introduces new concepts while keeping the previous functionality operational.

The goal is to build the application step by step, validate each part before moving forward, and keep the architecture maintainable.

## Packaging

The project uses CPack to create native packages:

### Fedora Linux

  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build --config Release
  cpack --config build/CPackConfig.cmake -G RPM

This produces an `OrderManager-1.0.0-Linux.rpm` package. Fedora users need the Qt 6 Widgets, GUI and SQLite runtime packages.

### Windows 11

Configure and build the Release configuration with Qt 6 and CMake, then run:

  cpack --config build/CPackConfig.cmake -G NSIS

The generated NSIS installer includes the Qt runtime and SQLite plugin through Qt's deployment support.

---

# V0 — Functional Prototype

The current version is **V0**.

The objective of V0 is to validate the basic architecture, product management system and graphical interface before introducing persistent storage.

## Features

- Create products
- Display products
- Update products
- Delete products
- Automatic product IDs
- Select a product
- Visual selection state
- Product hover effect
- Dark user interface
- Custom QSS styling
- In-memory storage

> **Important:** V0 stores products only in RAM. All data is lost when the application is closed.

---

# Architecture

The project separates the data model, application logic and user interface.

    OrderManager
         │
         ├── Models
         │     ├── Product
         │     └── ProductManager
         │
         └── UI
               ├── MainWindow
               ├── ProductDialog
               └── ProductItemWidget

This separation allows each component to have a clear responsibility.

---

## Product

`Product` represents a single product.

It currently contains:

- `id`
- `name`
- `price`

`Product` is responsible only for representing product information.

It does not manage the product list or the user interface.

---

## ProductManager

`ProductManager` manages the collection of products.

In V0, products are stored using:

    std::vector<Product>

It currently handles:

- Creating products
- Adding products
- Removing products
- Finding products by ID
- Providing access to the product collection

The UI does not directly manipulate the vector.

    MainWindow
         ↓
    ProductManager
         ↓
    std::vector<Product>

This separation will become important when persistent storage is introduced.

---

## MainWindow

`MainWindow` manages the main graphical interface.

It currently handles:

- Main application window
- Sidebar
- Product list
- Product selection
- New Product button
- Remove Product button
- Update Product button
- Communication with `ProductManager`

---

## ProductDialog

`ProductDialog` is used for both creating and updating products.

### Creating a product

    ProductDialog
         ↓
    ProductManager::createProduct()
         ↓
    Product created

### Updating a product

    ProductDialog
         ↓
    Product::setName()
    Product::setPrice()

Using the same dialog for both operations avoids unnecessary duplicated UI code.

---

## ProductItemWidget

`ProductItemWidget` represents one product visually inside the product list.

It displays:

- Product ID
- Product name
- Product price

It also handles the visual selected state.

The actual product management remains inside `ProductManager`.

---

# Project Structure

    OrderManager/
    │
    ├── assets/
    │   └── styles/
    │       └── main.qss
    │
    ├── include/
    │   ├── models/
    │   │   ├── Products.h
    │   │   └── ProductsManager.h
    │   │
    │   └── ui/
    │       ├── MainWindow.h
    │       ├── ProductDialog.h
    │       └── ProductItemWidget.h
    │
    ├── src/
    │   ├── models/
    │   │   ├── Product.cpp
    │   │   └── ProductsManager.cpp
    │   │
    │   ├── ui/
    │   │   ├── MainWindow.cpp
    │   │   ├── ProductDialog.cpp
    │   │   └── ProductItemWidget.cpp
    │   │
    │   └── main.cpp
    │
    ├── CMakeLists.txt
    └── README.md

---

# Data Flow

## Create

    User
      ↓
    ProductDialog
      ↓
    ProductManager::createProduct()
      ↓
    Product
      ↓
    std::vector<Product>
      ↓
    MainWindow
      ↓
    ProductItemWidget

## Read

    ProductManager
      ↓
    getProducts()
      ↓
    MainWindow
      ↓
    ProductItemWidget

## Update

    User
      ↓
    MainWindow
      ↓
    ProductManager::getProductById()
      ↓
    ProductDialog
      ↓
    Product::setName()
    Product::setPrice()
      ↓
    MainWindow refresh

## Delete

    User
      ↓
    MainWindow
      ↓
    ProductManager::removeProduct()
      ↓
    std::vector<Product>
      ↓
    MainWindow refresh

---

# Product Selection

The product list uses Qt's single-selection system.

    QAbstractItemView::SingleSelection

Only one product can be selected at a time.

The selection is synchronized between the `QListWidgetItem` and `ProductItemWidget`.

    QListWidgetItem
          ↓
       isSelected()
          ↓
    ProductItemWidget
          ↓
       setSelected()
          ↓
         QSS

C++ controls the selection state while QSS controls its visual appearance.

---

# QSS

The application uses Qt Style Sheets through:

    assets/styles/main.qss

The QSS currently controls:

- Main window colors
- Sidebar
- Buttons
- Inputs
- Product cards
- Hover states
- Selection states
- Dark theme
- Typography

Keeping the styling in QSS prevents visual logic from being mixed with the application logic.

---

# CRUD

V0 implements the complete basic CRUD workflow.

### Create

Create a new product through `ProductDialog` and `ProductManager`.

### Read

Retrieve products from `ProductManager` and display them through `ProductItemWidget`.

### Update

Select a product, open `ProductDialog`, modify its information and refresh the list.

### Delete

Select a product, remove it through `ProductManager` and refresh the list.

---

# Requirements

OrderManager is designed as a **cross-platform desktop application**.

Target platforms:

- Linux
- Windows
- macOS

Required:

- C++17
- Qt 6
- CMake 3.16+
- C++17 compatible compiler
- Ninja or another supported build system

---

# Linux — Fedora

Install the required development packages with:

    sudo dnf install gcc-c++ cmake ninja-build qt6-qtbase-devel

Other Linux distributions may require different package names.

---

# Windows

Required:

- Qt 6
- CMake
- C++17 compatible compiler
- Ninja or Visual Studio Build Tools

---

# macOS

Required:

- Qt 6
- CMake
- Xcode Command Line Tools
- C++17 compatible compiler
- Ninja or another supported build system

---

# Build

From the project directory:

    cmake -S . -B build -G Ninja
    cmake --build build

---

# Run

## Linux / macOS

    ./build/OrderManager

## Windows

    .\build\OrderManager.exe

---

# Storage Evolution

Storage will be introduced progressively.

The project intentionally does not start directly with a database.

The planned progression is:

    V0
    RAM
      ↓
    V1
    JSON
      ↓
    V2
    SQL

Each step introduces more complexity only after the previous architecture has been validated.

---

# V0 — RAM Storage

The current architecture is:

    ProductManager
         ↓
    std::vector<Product>
         ↓
         RAM

V0 is intentionally simple.

The objective is to validate:

- C++ classes
- Product model
- CRUD operations
- Qt interface
- Communication between classes
- Product selection
- General application architecture

No persistent storage is required at this stage.

---

# V1 — Local JSON Storage

**Status: Planned**

V1 will introduce the first real persistent storage system.

Products will be stored locally in a JSON file.

The architecture will become:

    UI
     ↓
    MainWindow
     ↓
    ProductManager
     ↓
    Persistence Layer
     ↓
    JSON
     ↓
    Local File

The main difference from V0 is that product information will survive application restarts.

## V1 Goals

- Save products to JSON
- Load products from JSON
- Load data when the application starts
- Save newly created products
- Save product modifications
- Save deletions
- Handle missing files
- Handle invalid JSON
- Separate storage logic from product management

The persistence system should remain separated from `ProductManager`.

`ProductManager` should not become responsible for all JSON file operations.

---

# V1 Data Flow

When the application starts:

    Application
         ↓
    Load JSON
         ↓
    Persistence Layer
         ↓
    Product data
         ↓
    ProductManager
         ↓
    MainWindow

When a product is modified:

    User
      ↓
    ProductManager
      ↓
    Persistence Layer
      ↓
    JSON File

---

# V1 Definition of Done

V1 will be considered complete when the application can:

1. Start
2. Load existing products
3. Create a product
4. Save the product
5. Close the application
6. Reopen the application
7. Find the product again
8. Update the product
9. Close and reopen the application
10. Verify that the modification remains
11. Delete the product
12. Close and reopen the application
13. Verify that the product has been deleted

At this point, OrderManager will have its first real persistent storage system.

---

# V2 — SQL Database

**Status: Planned**

Once JSON storage is working correctly, the project will progressively move toward a SQL database.

The architecture will become:

    UI
     ↓
    MainWindow
     ↓
    ProductManager
     ↓
    Database Layer
     ↓
    SQL
     ↓
    Database

## V2 Goals

- Database connection
- Database initialization
- Product table
- SQL CRUD operations
- Database error handling
- Database abstraction
- Relationships between entities

The objective is to move from simple local file storage to a structured database architecture.

---

# Why JSON Before SQL?

JSON is intentionally introduced before SQL.

The progression is:

    RAM
     ↓
    JSON
     ↓
    SQL

Each stage introduces a new concept.

### RAM

Focus:

- C++
- Classes
- Objects
- `std::vector`
- CRUD
- Qt

### JSON

Focus:

- Persistence
- Serialization
- Deserialization
- Files
- Error handling
- Storage abstraction

### SQL

Focus:

- Databases
- Tables
- Queries
- Relationships
- Database architecture

This approach keeps the project understandable while progressively increasing its complexity.

---

# V3 — Orders

**Status: Future**

Once products and database storage are stable, the project can introduce order management.

Potential features:

- Create orders
- Display orders
- Update orders
- Delete orders
- Order history
- Order status
- Product quantities
- Order totals
- Product/order relationships

The data model will then become more relational.

    Product
       ↓
    Order Item
       ↓
    Order

---

# V4 — Complete Management System

**Status: Future**

The long-term goal is to evolve OrderManager into a complete management application.

Potential features:

- Products
- Orders
- Inventory
- Customers
- Search
- Filtering
- Sorting
- Dashboard
- Reports
- Statistics
- Settings
- Authentication
- User management
- Notifications
- Advanced UI

The exact features will be defined as the project progresses.

---

# Roadmap

## V0 — Functional Prototype

**Status: Complete**

### Objective

Build and validate the fundamental application.

### Features

- Product model
- Product manager
- Product CRUD
- RAM storage
- Product list
- Product selection
- Hover effect
- Product dialog
- Custom QSS interface

---

## V1 — Local JSON Persistence

**Status: Planned**

### Objective

Make OrderManager capable of permanently storing its data.

### Storage

**Local JSON file**

### Main Goals

- JSON serialization
- JSON deserialization
- Save products
- Load products
- Persistent data
- Persistence layer
- Error handling
- UI improvements

---

## V2 — SQL Database

**Status: Planned**

### Objective

Replace local JSON storage with a real database.

### Main Goals

- Database connection
- Database initialization
- SQL queries
- Product table
- SQL CRUD
- Error handling
- Database abstraction
- Relationships

---

## V3 — Orders

**Status: Future**

### Objective

Introduce order management and relationships between products and orders.

---

## V4 — Complete Management System

**Status: Future**

### Objective

Transform OrderManager into a complete management application.

---

# Cross-Platform Goal

OrderManager is designed to run on:

    OrderManager
         │
         ├── Linux
         ├── Windows
         └── macOS

Qt provides the cross-platform GUI framework while C++ handles the application logic.

The goal is to keep the core application independent from the operating system.

---

# Development Philosophy

OrderManager is developed version by version.

Each version should be functional before moving to the next major architectural change.

    Build
      ↓
    Test
      ↓
    Fix
      ↓
    Validate
      ↓
    Next Version

The objective is not to create the biggest application as quickly as possible.

The objective is to build a clean foundation and progressively turn it into a complete application.

---

# Architectural Philosophy

The project aims to avoid unnecessary coupling between components.

For example, the UI should not need to know how product data is physically stored.

V0:

    MainWindow
        ↓
    ProductManager
        ↓
    std::vector<Product>

V1:

    MainWindow
        ↓
    ProductManager
        ↓
    Persistence Layer
        ↓
    JSON

V2:

    MainWindow
        ↓
    ProductManager
        ↓
    Database Layer
        ↓
    SQL

This means the storage system can evolve without requiring the entire user interface to be rewritten.

---

# Learning Objectives

OrderManager is also a practical C++ and software architecture project.

The project progressively covers:

- C++
- Object-Oriented Programming
- Classes
- References
- Pointers
- STL containers
- `std::vector`
- CRUD operations
- Qt 6
- Widgets
- Signals and slots
- Event-driven programming
- Qt layouts
- QSS
- UI architecture
- JSON
- File handling
- Serialization
- Persistence
- SQL
- Databases
- Database relationships
- Software architecture
- Cross-platform development
- UI/UX

---

# Final Vision

The long-term vision is to transform the initial CRUD prototype into a complete, persistent and structured management application.

    V0
    Functional Prototype
    RAM
       ↓
    V1
    Local Persistence
    JSON
       ↓
    V2
    Database
    SQL
       ↓
    V3
    Orders
    Relationships
       ↓
    V4
    Complete Management System

The project is not only about creating an application.

It is also about progressively learning how a real software project is structured, developed, tested and expanded.

---

# Current Status

## V0 — Complete

The first functional CRUD prototype is complete.

Current capabilities:

- Product creation
- Product display
- Product update
- Product deletion
- Automatic IDs
- Product selection
- Product hover
- Custom QSS interface
- Dark theme
- RAM storage

## Next Milestone

### V1 — Local JSON Persistence

The next major objective is to introduce persistent local storage.

Products will be saved to a JSON file and loaded when the application starts.

This will be the first version where OrderManager actually retains information between application sessions.
