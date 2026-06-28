# Inventory Management System — CAMTECH

## Problem Statement

A console-based C application to manage product stock-in/stock-out, monitor low-stock levels, and generate inventory valuation reports. Data is persisted to binary files with an audit trail of all stock movements.

## Documentation

- [feature.md](feature.md) — Feature requirements, task distribution, and user flow
- [CONVENTIONS.md](CONVENTIONS.md) — Branching strategy, naming conventions, commit format, code style

## Build Instructions

### Make
```bash
make          # compile
make run      # compile and run
make clean    # remove binaries and data files
```

### CMake
```bash
mkdir build && cd build
cmake ..
make
./inventory
```

## Features

- Add products with auto-generated codes (PRD001, PRD002, ...)
- Stock in / Stock out with quantity validation
- Search product by code or name (partial, case-insensitive)
- Low-stock warning (quantity < minimum stock threshold)
- Total inventory value (quantity x price)
- Audit log with timestamps for all transactions
- Full input validation on all user inputs

## Usage

Run the program, then select from the menu:

```
1. Add Product       — Enter name, qty, price, min stock (code auto-generated)
2. Stock In          — Increase quantity of existing product
3. Stock Out         — Decrease quantity (cannot exceed available stock)
4. Search Product    — By code (exact) or by name (partial match)
5. Low Stock Report  — Lists products below their minimum threshold
6. Inventory Value   — Shows qty x price per product + grand total
7. View Audit Log    — Displays all stock movements with timestamps
8. Exit              — Quit the program
```

## Technical Stack

| Component | Detail |
|-----------|--------|
| Language | C (C11 standard) |
| Build | Make / CMake |
| Data file | inventory.dat (binary, fixed-size Product records) |
| Log file | transactions.log (text, append-only) |
| File I/O | Direct file-as-database (every operation writes immediately) |
| Validation | Input type checks, stock-out guards, code uniqueness |

## File Structure

```
inventory-camtech/
├── README.md
├── CONVENTIONS.md
├── CMakeLists.txt
├── Makefile
├── feature.md
├── .gitignore
├── inventory.h         ← struct Product, constants
├── file_db.h           ← DB SDK prototypes
├── file_db.c           ← DB SDK implementation (all file I/O)
├── utils.h             ← Utility function prototypes
├── utils.c             ← Utility function implementations
├── features.h          ← Feature function prototypes
├── features.c          ← Feature implementations
├── src/
│   └── main.c          ← Entry point, menu loop
├── inventory.dat       ← Generated binary product data
└── transactions.log    ← Generated audit trail
```

## Project Team

| Person | Feature | Responsibility |
|--------|---------|----------------|
| 1 | FR1 | Database SDK — all file I/O (insert, get, update, log) |
| 2 | FR2 | Add product + search product |
| 3 | FR3 | Stock in + stock out with validation |
| 4 | FR4 | Low-stock report, inventory value, view audit log |
| 5 | FR5 | Main menu, input utilities, Makefile, CMakeLists.txt |

## Deliverables

- Problem statement and pseudocode (feature.md)
- Flowchart (separate file)
- Menu-driven C program with 22 functions
- File handling for persistence
- Input validation on all user inputs
- Auto-generated product codes
- Program output screenshots (to be captured)
- Final presentation and live demo (to be scheduled)
