# Inventory Management System Flowchart

## 1. Main flow

```mermaid
flowchart TD
    A["Start"] --> B["Show menu"]
    B --> C{"Choose option"}
    C -->|1| D["Add product"]
    C -->|2| E["Stock in"]
    C -->|3| F["Stock out"]
    C -->|4| G["Search product"]
    C -->|5| H["Low stock report"]
    C -->|6| I["Inventory value"]
    C -->|7| J["View audit log"]
    C -->|8| K["Exit"]

    D --> B
    E --> B
    F --> B
    G --> B
    H --> B
    I --> B
    J --> B
```

## 2. Add product flow

```mermaid
flowchart TD
    A["Start addProduct"] --> B["Generate code"]
    B --> C["Enter name"]
    C --> D["Enter quantity"]
    D --> E["Enter price"]
    E --> F["Enter minimum stock"]
    F --> G["Save product"]
    G --> H["Write audit log"]
    H --> I["Done"]
```

## 3. Stock in flow

```mermaid
flowchart TD
    A["Start stockIn"] --> B["Enter product code"]
    B --> C{"Product found?"}
    C -->|No| D["Show not found"]
    C -->|Yes| E["Enter quantity to add"]
    E --> F["Update stock"]
    F --> G["Write audit log"]
    G --> H["Done"]
    D --> I["Back to menu"]
```

## 4. Stock out flow

```mermaid
flowchart TD
    A["Start stockOut"] --> B["Enter product code"]
    B --> C{"Product found?"}
    C -->|No| D["Show not found"]
    C -->|Yes| E["Enter quantity to remove"]
    E --> F{"Enough stock?"}
    F -->|No| G["Show error"]
    F -->|Yes| H["Update stock"]
    H --> I["Write audit log"]
    I --> J["Done"]
    G --> K["Back to menu"]
    D --> K
```

## 5. Search product flow

```mermaid
flowchart TD
    A["Start searchProduct"] --> B{"Search by code or name"}
    B -->|Code| C["Enter code"]
    B -->|Name| D["Enter name"]
    C --> E["Find product"]
    D --> F["Search all products"]
    E --> G{"Found?"}
    F --> H{"Match found?"}
    G -->|Yes| I["Display product"]
    G -->|No| J["Show not found"]
    H -->|Yes| K["Display matches"]
    H -->|No| L["Show no matches"]
    I --> M["Done"]
    J --> M
    K --> M
    L --> M
```

## 6. Reports flow

```mermaid
flowchart TD
    A["Start report"] --> B["Read all products"]
    B --> C{"Report type"}
    C -->|Low stock| D["Find below minimum stock"]
    C -->|Inventory value| E["Calculate value of each product"]
    D --> F["Display report"]
    E --> G["Show total value"]
    F --> H["Done"]
    G --> H
```

## 7. Audit log flow

```mermaid
flowchart TD
    A["Start audit view"] --> B["Read transaction log"]
    B --> C["Display log"]
    C --> D["Done"]
```

## Module overview

- Main program flow: [src/main.c](src/main.c)
- Product creation: [src/add_product.c](src/add_product.c)
- Stock in/out: [src/stock.c](src/stock.c)
- Search: [src/search.c](src/search.c)
- Reports: [src/reports.c](src/reports.c)
- Audit log: [src/audit.c](src/audit.c)
- File operations: [src/fileio.c](src/fileio.c)