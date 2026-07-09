# Inventory Management System — CAMTECH

## Problem Statement

A console-based C application to manage product stock-in/stock-out, monitor low-stock levels, and generate inventory valuation reports. Data is persisted to binary files with an audit trail of all stock movements.

## Documentation

- [docs/feature.md](docs/feature.md) — Feature requirements, task distribution, and user flow
- [docs/CONVENTIONS.md](docs/CONVENTIONS.md) — Branching strategy, naming conventions, commit format, code style
- [docs/feature.md](docs/feature.md) — Per-user flowcharts in the "User Flowcharts" section (Thina, Lida, Samrith, Kelly, Lado, Rith)

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
├── src/
│   ├── main.c          ← FR6: Entry point, menu loop
│   ├── fileio.h        ← FR1: DB SDK prototypes
│   ├── fileio.c        ← FR1: DB SDK implementation (core binary DB)
│   ├── utils.h         ← FR6: Utility function prototypes
│   ├── utils.c         ← FR2/FR3/FR4: Shared utility implementations
│   ├── features.h       ← FR6: Master include header
│   ├── add_product.h/c  ← FR2: Add Product, Gen Code, Append Log, Read Float
│   ├── stock.h/c       ← FR3: Stock In/Out, Count Products, Read Int
│   ├── search.h/c      ← FR4: Search Product, Read String, To Lower
│   ├── reports.h/c     ← FR5: Reports, Audit Viewer
│   └── audit.h/c       ← FR4: Audit Log file operations
├── inventory.dat       ← Generated binary product data
└── transactions.log    ← Generated audit trail
```

## Project Team

| Person | Feature | Responsibility |
|--------|---------|----------------|
| Thina | FR1 | Database SDK — core binary DB ops (insert, get by code, update qty, get all) |
| Lida | FR2 | Add Product, Generate Product Code, Append Audit Log, Read Float |
| Samrith | FR3 | Stock In/Out, Count Products, Read Integer |
| Kelly | FR4 | Search Product, View Audit Log (file ops), Read String, To Lower |
| Lado | FR5 | Low-stock report, inventory value, View Audit Log (UI), Build system |
| Rith | FR6 | Main menu, program entry point, shared header files |

## Deliverables

- Problem statement and pseudocode (feature.md)
- Flowchart (separate file)
- Menu-driven C program with 22 functions
- File handling for persistence
- Input validation on all user inputs
- Auto-generated product codes
- Program output screenshots (to be captured)
- Final presentation and live demo (to be scheduled)
