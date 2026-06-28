# Inventory Management System — Feature Requirements

## User Flow — Terminal UI

```text
====================================
  INVENTORY MANAGEMENT SYSTEM
         - CAMTECH -
====================================
  Group Members:
  1. Person 1 - File DB SDK
  2. Person 2 - Add & Search
  3. Person 3 - Stock In & Out
  4. Person 4 - Reports & Audit
  5. Person 5 - Main Menu & Utils
====================================

====================================
  INVENTORY MANAGEMENT SYSTEM
         - CAMTECH -
====================================
1. Add Product
2. Stock In
3. Stock Out
4. Search Product
5. Low Stock Report
6. Inventory Value
7. View Audit Log
8. Exit
------------------------------------
Enter your choice: 1

--- Add Product ---
Generated code: PRD001
Enter product name: 
Name cannot be empty.
Enter product name: Wrench
Enter quantity: -5
Quantity cannot be negative.
Enter quantity: 50
Enter price: 0
Price must be positive.
Enter price: 15.99
Enter minimum stock level: -1
Minimum stock cannot be negative.
Enter minimum stock level: 10
Product added successfully!

Enter your choice: 1

--- Add Product ---
Generated code: PRD002
Enter product name: Hammer
Enter quantity: 5
Enter price: 12.50
Enter minimum stock level: 10
Product added successfully!

Enter your choice: 1

--- Add Product ---
Generated code: PRD003
Enter product name: Screwdriver
Enter quantity: 3
Enter price: 8.75
Enter minimum stock level: 10
Product added successfully!

Enter your choice: 3

--- Stock Out ---
Enter product code: PRD999
Product not found.

Enter your choice: 3

--- Stock Out ---
Enter product code: PRD001
Current quantity: 50
Enter quantity to remove: -2
Quantity must be positive.
Enter quantity to remove: 10
Stock out successful! Remaining: 40

Enter your choice: 3

--- Stock Out ---
Enter product code: PRD002
Current quantity: 5
Enter quantity to remove: 10
Insufficient stock. Available: 5

Enter quantity to remove: 3
Stock out successful! Remaining: 2

Enter your choice: 2

--- Stock In ---
Enter product code: PRD002
Current quantity: 2
Enter quantity to add: -5
Quantity must be positive.
Enter quantity to add: 15
Stock in successful! New quantity: 17

Enter your choice: 4

--- Search Product ---
1. Search by Code
2. Search by Name
Enter choice (1-2): 1
Enter product code: PRD999
Product not found.

Enter your choice: 4

--- Search Product ---
1. Search by Code
2. Search by Name
Enter choice (1-2): 1
Enter product code: PRD001

Code       Name                 Qty        Price
--------------------------------------------------------
PRD001     Wrench               40         15.99

Enter your choice: 4

--- Search Product ---
1. Search by Code
2. Search by Name
Enter choice (1-2): 2
Enter product name (or part): Drill
No matching products found.

Enter your choice: 4

--- Search Product ---
1. Search by Code
2. Search by Name
Enter choice (1-2): 2
Enter product name (or part): screw

Code       Name                 Qty        Price
--------------------------------------------------------
PRD003     Screwdriver          3          8.75

Enter your choice: 5

--- Low Stock Report ---

Code       Name                 Qty        Min        Status
--------------------------------------------------------
PRD003     Screwdriver          3          10         LOW STOCK

Enter your choice: 5

--- Low Stock Report ---
All products are adequately stocked.

Enter your choice: 6

--- Inventory Value Report ---

Code       Name                 Qty        Unit Price   Total
--------------------------------------------------------
PRD001     Wrench               40         15.99        639.60
PRD002     Hammer               17         12.50        212.50
PRD003     Screwdriver          3          8.75         26.25
--------------------------------------------------------
GRAND TOTAL: 878.35

--- Low Stock Warnings ---
  PRD003 (Screwdriver): 3 remaining (min: 10)

Enter your choice: 7

--- Audit Log ---
[2026-06-28 10:30:15] PRODUCT_ADD code=PRD001 qty=50
[2026-06-28 10:32:40] PRODUCT_ADD code=PRD002 qty=5
[2026-06-28 10:35:00] PRODUCT_ADD code=PRD003 qty=3
[2026-06-28 10:36:12] STOCK_OUT code=PRD001 qty=10
[2026-06-28 10:37:55] STOCK_OUT code=PRD002 qty=3
[2026-06-28 10:39:22] STOCK_IN code=PRD002 qty=15

Enter your choice: abc
Invalid input. Enter your choice: 8

Exiting... Goodbye!
```

---

## Project Overview

Console-based C application for product inventory management. Supports stock-in/stock-out, low-stock alerts, inventory valuation, and audit logging. Uses direct file-as-database approach — every operation reads or writes immediately to the data file. A centralized file-handling module owns all file input/output, and feature functions never access files directly.

---

## Architecture

The program has four layers:

- FR5 (UI/Menu) in main.c — menu loop, input validation, utility functions
- FR2, FR3, FR4 in features.c — adding products, stock movements, search, and reports
- FR1 (Database SDK) in file_db.c — the only module that opens, reads, writes, or closes files
- Data files — inventory.dat (binary product records) and transactions.log (text audit trail)

---

## Shared Files

| File | Who writes | Purpose |
|------|-----------|---------|
| inventory.h | FR5 | Product structure definition and constants |
| utils.h, utils.c | FR5 | Input reading utilities used by all features |
| features.h | FR5 | Function prototypes for all feature functions |
| file_db.h | FR1 | Database SDK function prototypes |
| file_db.c | FR1 | Database SDK implementation |

---

## Integration Order

1. FR5 creates the shared headers inventory.h, utils.h, utils.c, and features.h
2. FR1 creates file_db.h and file_db.c with all 8 database methods
3. FR2, FR3, and FR4 write their feature functions in features.c (can work in parallel)
4. FR5 creates main.c, Makefile, and CMakeLists.txt, then compiles and tests

---

## Data Structures

The Product structure holds: a code that is auto-generated in format PRD001, PRD002 and so on, a name, the current quantity in stock, the unit price, and a minimum stock threshold for low-stock warnings.

The file inventory.dat stores these Product records as fixed-size binary entries written one after another.

The file transactions.log stores timestamped audit entries in the format showing date and time, the action performed, the product code involved, and the quantity.

---

## Input Validation Rules

Product codes are auto-generated and never entered by the user. Product names must be non-empty and at most 49 characters. Initial quantity cannot be negative. Price must be greater than zero. Minimum stock level cannot be negative. When adding stock, the quantity must be positive. When removing stock, the quantity must be positive and cannot exceed the current available stock. Menu choices must be a number between 1 and 8. If the user enters non-numeric input where a number is expected, the program re-prompts until valid input is given.

---

## FR1 — Database SDK Layer

Person 1 writes file_db.h and file_db.c. This is the only module that opens, reads, writes, seeks, or closes files. All database method names use the db_ prefix. This feature has no dependencies on other features.

### Task 1.1 — Insert Product

Takes a populated Product structure and appends it as a new record at the end of inventory.dat in binary append mode. Returns 1 if the write succeeded and 0 if the file could not be opened.

### Task 1.2 — Get Product by Code

Takes a product code string. Opens inventory.dat in read binary mode and reads records one by one. If a record with a matching code is found, it copies that record into the output parameter and returns 1. If no match is found or the file does not exist, returns 0.

### Task 1.3 — Update Product Quantity

Takes a product code and a new quantity value. Opens inventory.dat in read-write binary mode and reads records sequentially until it finds a match. Once found, it steps back by one record and overwrites the quantity field in place. Returns 1 on success and 0 if the product was not found.

### Task 1.4 — Get All Products

Takes an output array and a maximum count. Opens inventory.dat in read binary mode and reads as many records as possible up to the maximum. Returns the actual number of records that were read.

### Task 1.5 — Count Products

Opens inventory.dat in read binary mode, seeks to the end of the file, and divides the total file size by the size of one Product record to calculate the total number of records. Returns 0 if the file does not exist.

### Task 1.6 — Generate Product Code

Scans all existing product codes in inventory.dat by reading records one by one. Extracts the numeric suffix from each code, finds the highest number, and increments it by one. Formats the result as PRD followed by a three-digit number, for example PRD001, PRD002, and so on. If the file does not exist or is empty, starts at PRD001.

### Task 1.7 — Append to Audit Log

Takes an action name, a product code, and a quantity. Opens transactions.log in append text mode. Gets the current system time using time functions, formats it as a readable timestamp, and writes a single line to the log showing the timestamp, the action name, the product code, and the quantity. Closes the file afterward.

### Task 1.8 — View Audit Log

Opens transactions.log in read text mode. If the file does not exist, prints a message saying no transactions were recorded. Otherwise, reads the file line by line and prints each line to the console. Closes the file when done.

---

## FR2 — Product Creation and Search

Person 2 writes into features.c. This feature handles adding new products to inventory with full input validation and searching for existing products. It calls FR1 methods to generate codes, insert products, retrieve single products, and retrieve all products. It uses shared utility functions for reading integers, floats, strings, and converting text to lowercase.

### Task 2.1 — Add Product

Displays a header message. Calls the code generator from FR1 to get the next available product code and displays it. Then repeatedly prompts the user for a product name until a non-empty entry is given. Prompts for quantity and validates that it is not negative. Prompts for price and validates that it is greater than zero. Prompts for minimum stock level and validates that it is not negative. Creates a Product structure with all the entered values and the generated code. Calls FR1 to insert the product into the data file, then calls FR1 to log the creation in the audit log. Prints a success or failure message.

Validation examples:
- Empty name entered: prints Name cannot be empty and re-prompts
- Negative quantity like -5: prints Quantity cannot be negative and re-prompts
- Zero or negative price like 0: prints Price must be positive and re-prompts
- Negative minimum stock like -1: prints Minimum stock cannot be negative and re-prompts

### Task 2.2 — Search Product

Displays a header message and asks the user to choose between searching by code or by name.

If searching by code, the user enters a product code and FR1 looks it up. If found, the product details are displayed in a formatted table. If not found, prints Product not found.

If searching by name, the user enters a full or partial product name. FR1 retrieves all products from the data file. The search term and each product name are converted to lowercase for case-insensitive comparison. Each product whose name contains the search term is displayed in a formatted table. If no matches are found, prints No matching products found.

---

## FR3 — Stock Movement

Person 3 writes into features.c. This feature handles increasing and decreasing product stock quantities with validation. It calls FR1 methods to retrieve a product, update its quantity, and log the movement. It uses shared utility functions for reading integers and strings.

### Task 3.1 — Stock In

Displays a header message and prompts for a product code. Calls FR1 to look up the product. If not found, prints Product not found and returns. Otherwise displays the current quantity. Then repeatedly prompts for the quantity to add until a positive number is entered. Adds the entered quantity to the current quantity. Calls FR1 to update the product record in the data file and to log the stock-in event. Prints the new quantity.

Validation examples:
- Product code that does not exist: prints Product not found and returns to menu
- Negative or zero quantity like -5 or 0: prints Quantity must be positive and re-prompts

### Task 3.2 — Stock Out

Displays a header message and prompts for a product code. Calls FR1 to look up the product. If not found, prints Product not found and returns. Otherwise displays the current quantity. Then repeatedly prompts for the quantity to remove until a positive number that does not exceed the available stock is entered. If the user enters a quantity larger than the current stock, prints Insufficient stock. Available: X and the prompt repeats. Subtracts the entered quantity from the current quantity. Calls FR1 to update the product record and to log the stock-out event. Prints the remaining quantity.

Validation examples:
- Product code that does not exist: prints Product not found and returns to menu
- Negative quantity like -2: prints Quantity must be positive and re-prompts
- Quantity exceeding available stock like 10 when only 5 available: prints Insufficient stock. Available: 5 and re-prompts

---

## FR4 — Reports and Audit Viewer

Person 4 writes into features.c. This feature generates reports and displays the audit log. It calls FR1 methods to retrieve all products and to view the audit log.

### Task 4.1 — Low Stock Report

Retrieves all products from the data file using FR1. If there are no products, prints a message and returns. Otherwise displays a table header with columns for code, name, quantity, minimum stock, and status. Loops through all products and prints those whose quantity is below their minimum stock threshold with a status label indicating LOW STOCK. If no products are below their minimum, prints All products are adequately stocked.

### Task 4.2 — Inventory Value Report

Retrieves all products from the data file using FR1. If there are no products, prints a message and returns. Otherwise displays a table with columns for code, name, quantity, unit price, and total value, where the total value is the product of quantity and unit price. Calculates a grand total by adding up all line totals. Displays the grand total below the table. Then prints a separate low-stock warnings section showing each product that is below its minimum threshold along with its current and minimum quantities.

### Task 4.3 — View Audit Log

Displays a header message and calls FR1 to read and display the entire audit log from transactions.log.

---

## FR5 — Main Menu and System Integration

Person 5 writes main.c, Makefile, CMakeLists.txt, inventory.h, features.h, utils.h, and utils.c. This feature provides the program entry point, the menu display, shared input utility functions, the build system, and all shared header files.

### Task 5.1 — Display Menu

Prints a formatted menu showing eight options: add product, stock in, stock out, search product, low stock report, inventory value, view audit log, and exit.

### Task 5.2 — Main Entry Point

Prints the project banner with group member names. Then repeatedly displays the menu and reads the user's choice. Based on the choice, it dispatches to the appropriate feature function from FR2, FR3, or FR4. Exits the program when the user selects option 8. If the user enters a number outside 1 to 8, prints Invalid choice. Enter 1-8 and re-prompts.

Validation examples:
- Non-numeric input like abc: prints Invalid input and re-prompts
- Number outside range like 9: prints Invalid choice. Enter 1-8 and re-prompts

### Task 5.3 to 5.6 — Utility Functions

Provides four shared utility functions used by all features. The integer input function displays a prompt, reads a line using fgets, parses it with sscanf, and returns the integer value. If the input is not a valid integer, prints Invalid input and re-prompts. The float input function works the same way but parses a floating-point number, re-prompting on invalid input. The read string function displays a prompt, reads a line with fgets, and removes the trailing newline character. The lowercase conversion function copies a source string to a destination string converting each character to lowercase.

### Task 5.7 — Build System

Provides a Makefile and CMakeLists.txt that compile the project. The main.c source file is located in a src directory and includes the utilities header file from the parent directory. The build system compiles main.c, file_db.c, features.c, and utils.c, and links them into an executable called inventory. Targets are provided for building, running, and cleaning up.

---

## Complete Function Call Map

The main function in FR5 calls feature functions from FR2, FR3, and FR4. Each feature function calls one or more database methods from FR1. FR1 methods are the only ones that directly access the data files.

Add product calls FR1 to generate a code, insert the product, and append to the audit log. Stock in and stock out both call FR1 to get the product, update its quantity, and append to the audit log. Search product calls FR1 to get a single product by code or to get all products. Low stock report and inventory value both call FR1 to get all products. View audit log calls FR1 to display the log.

---

## Task Distribution Summary

| Feature | Person | Files | Tasks |
|---------|--------|-------|-------|
| FR1 | 1 | file_db.h, file_db.c | 8 tasks (insert, get, update, list all, count, generate code, append log, view log) |
| FR2 | 2 | features.c | 2 tasks (add product, search product) |
| FR3 | 3 | features.c | 2 tasks (stock in, stock out) |
| FR4 | 4 | features.c | 3 tasks (low stock report, inventory value, view audit log) |
| FR5 | 5 | main.c, Makefile, CMakeLists.txt, inventory.h, features.h, utils.h, utils.c | 7 tasks (menu display, main loop, 4 utilities, build system) |

---

## Program Run Example

When the program starts, it displays a banner listing the project title and the five group members. It then shows the main menu with eight options. The user selects options by typing the corresponding number.

If the user selects option 1 to add a product, the program generates a code like PRD001 and displays it. The user then enters the product name, quantity, price, and minimum stock level. After all values are entered and validated, the program saves the product and confirms success.

If the user selects option 3 for stock out and enters a quantity larger than what is available, the program shows an error with the available quantity and re-prompts until a valid amount is entered.

If the user selects option 4 to search, they can choose between searching by exact code or by partial name. When searching by name, entering only part of the name returns all matching products.

If the user selects option 5, only products whose quantity is below their minimum stock level are shown with a warning label. If all products are adequately stocked, a message to that effect is displayed.

If the user selects option 6, a full inventory valuation table is shown with per-product totals and a grand total, followed by any low-stock warnings.

If the user selects option 7, the complete audit log is displayed showing every product addition and stock movement with timestamps.

If the user enters non-numeric input for the menu choice, an error message is shown and the prompt repeats. The program exits cleanly when the user selects option 8.

---

## Deliverables

| Item | Status |
|------|--------|
| Problem statement | In README.md |
| Algorithm and pseudocode | In this document |
| Flowchart | Separate image or hand-drawn |
| Menu-driven C program | Multiple source files as described above |
| At least five meaningful functions | More than twenty total across all features |
| Use of array and structure | Product structure and array in get all products |
| File handling for persistence | Binary data file and text audit log |
| Input validation | All numeric and text inputs validated with re-prompting |
| Auto-generated product codes | PRD001, PRD002 format via code generator |
| Program screenshots | To be captured |
| Final presentation and demo | To be scheduled |
