# User Flowcharts

Flowcharts for each team member's feature area. Each diagram shows the
control flow of the primary menu-driven tasks owned by that user.

---

## Thina — FR1: Database SDK (file_db)

Owns all binary I/O on `inventory.dat`.

```mermaid
flowchart TD
    A[Start] --> B{Operation?}
    B -->|Insert| C[Open inventory.dat append]
    C --> D[fwrite Product record]
    D --> E[Return 1 if written else 0]
    B -->|Get by code| F[Open inventory.dat read]
    F --> G{Read record}
    G -->|match code| H[Copy to out, return 1]
    G -->|no more records| I[Return 0]
    G -->|next| G
    B -->|Update qty| J[Open inventory.dat r+]
    J --> K{Read record}
    K -->|match code| L[Seek back one record]
    L --> M[Overwrite quantity]
    M --> N[Return 1]
    K -->|no more records| O[Return 0]
    K -->|next| K
    B -->|Get all| P[Open inventory.dat read]
    P --> Q[Read up to max into array]
    Q --> R[Return count read]
```

---

## Lida — FR2: Add Product

Owns product creation, code generation, and audit append.

```mermaid
flowchart TD
    A[Add Product selected] --> B[Generate next code PRDxxx]
    B --> C[Display generated code]
    C --> D{Prompt name}
    D -->|empty| D
    D --> E{Prompt quantity}
    E -->|negative| E
    E --> F{Prompt price}
    F -->|not positive| F
    F --> G{Prompt min stock}
    G -->|negative| G
    G --> H[Build Product struct]
    H --> I[FR1 insert product]
    I --> J[Append audit log ADD]
    J --> K[Print success/failure]
```

---

## Samrith — FR3: Stock In / Stock Out

Owns stock movement and product counting.

```mermaid
flowchart TD
    A{Stock In or Out?} -->|Stock In| B[Prompt code]
    A -->|Stock Out| C[Prompt code]
    B --> D[FR1 get product]
    C --> D
    D -->|not found| Z[Print Product not found, return]
    D -->|found| E[Show current quantity]
    E --> F{Prompt qty}
    F -->|not positive| F
    F -->|Stock Out and qty > stock| G[Print Insufficient stock, repeat]
    G --> F
    F --> H[newQty = qty +/- entered]
    H --> I[FR1 update quantity]
    I --> J[Append audit log IN/OUT]
    J --> K[Print updated quantity]
```

---

## Kelly — FR4: Search & Audit Log

Owns search by code/name and audit log viewing.

```mermaid
flowchart TD
    A[Search Product selected] --> B{Search by code or name?}
    B -->|Code| C[Prompt code]
    C --> D[FR1 get by code]
    D -->|found| E[Display product table]
    D -->|not found| F[Print Product not found]
    B -->|Name| G[Prompt partial name]
    G --> H[FR1 get all products]
    H --> I[Lowercase term + names]
    I --> J{Match?}
    J -->|yes| K[Display product table]
    J -->|no matches| L[Print No matching products]
    M[View Audit Log selected] --> N[Open transactions.log]
    N -->|missing| O[Print No transactions recorded]
    N -->|exists| P[Print each line]
```

---

## Lado — FR5: Reports & Build

Owns low-stock report, inventory value, audit viewer UI, and build system.

```mermaid
flowchart TD
    A{Report type?} -->|Low Stock| B[FR1 get all products]
    A -->|Inventory Value| C[FR1 get all products]
    A -->|View Audit Log| D[FR4 view audit log]
    B -->|empty| E[Print message, return]
    B -->|has data| F[Print table, flag qty < min]
    C -->|empty| G[Print message, return]
    C -->|has data| H[Print qty x price table + grand total]
    H --> I[Print low-stock warnings]
    D --> J[Display log to console]
```

---

## Rith — FR6: Main Menu & Integration

Owns program entry point, menu loop, and shared headers.

```mermaid
flowchart TD
    A[Program start] --> B[Print banner with members]
    B --> C[Display menu 1-8]
    C --> D[Read choice]
    D -->|not 1-8| E[Print Invalid choice, repeat]
    E --> C
    D -->|1| F[FR2 add product]
    D -->|2| G[FR3 stock in]
    D -->|3| H[FR3 stock out]
    D -->|4| I[FR4 search]
    D -->|5| J[FR5 low stock]
    D -->|6| K[FR5 inventory value]
    D -->|7| L[FR5 view audit log]
    D -->|8| M[Exit]
    F --> C
    G --> C
    H --> C
    I --> C
    J --> C
    K --> C
    L --> C
```
