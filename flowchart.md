# Inventory Management System Flowchart

```mermaid
flowchart TD
    A["Start main"] --> B["Display welcome banner"]
    B --> C["Show main menu"]
    C --> D{"User choice"}

    D -->|1| E["Add product"]
    D -->|2| F["Stock in"]
    D -->|3| G["Stock out"]
    D -->|4| H["Search product"]
    D -->|5| I["Low stock report"]
    D -->|6| J["Inventory value"]
    D -->|7| K["View audit log"]
    D -->|8| L["Exit program"]

    E --> E1["Generate product code"]
    E1 --> E2["Read product name"]
    E2 --> E3["Read quantity"]
    E3 --> E4["Read price"]
    E4 --> E5["Read minimum stock"]
    E5 --> E6["Insert product"]
    E6 --> E7["Append log"]
    E7 --> C

    F --> F1["Read product code"]
    F1 --> F2["Find product"]
    F2 -->|Found| F3["Read quantity to add"]
    F2 -->|Not found| F4["Show not found"]
    F3 --> F5["Update quantity"]
    F5 --> F6["Update product file"]
    F6 --> F7["Append log"]
    F4 --> C
    F7 --> C

    G --> G1["Read product code"]
    G1 --> G2["Find product"]
    G2 -->|Found| G3["Read quantity to remove"]
    G2 -->|Not found| G4["Show not found"]
    G3 --> G5["Validate stock availability"]
    G5 --> G6["Update quantity"]
    G6 --> G7["Update product file"]
    G7 --> G8["Append log"]
    G4 --> C
    G8 --> C

    H --> H1{"Search by"}
    H1 -->|Code| H2["Read code"]
    H2 --> H3["Find product"]
    H3 -->|Found| H4["Display product"]
    H3 -->|Not found| H5["Show not found"]
    H1 -->|Name| H6["Read name search term"]
    H6 --> H7["Read all products"]
    H7 --> H8["Match name pattern"]
    H8 --> H9["Display matching products"]
    H4 --> C
    H5 --> C
    H9 --> C

    I --> I1["Read all products"]
    I1 --> I2["Find items below minimum stock"]
    I2 --> I3["Display low stock report"]
    I3 --> C

    J --> J1["Read all products"]
    J1 --> J2["Compute total value per product"]
    J2 --> J3["Show grand total and warnings"]
    J3 --> C

    K --> K1["View transaction log"]
    K1 --> C

    E6 --> M["inventory.dat"]
    F6 --> M
    G7 --> M
    H3 --> M
    H7 --> M
    I1 --> M
    J1 --> M

    E7 --> N["transactions.log"]
    F7 --> N
    G8 --> N
    K1 --> N
```

## Module overview

- Main program flow: [src/main.c](src/main.c)
- Product creation: [src/add_product.c](src/add_product.c)
- Stock in/out: [src/stock.c](src/stock.c)
- Search: [src/search.c](src/search.c)
- Reports: [src/reports.c](src/reports.c)
- Audit log: [src/audit.c](src/audit.c)
- File operations: [src/fileio.c](src/fileio.c)
a