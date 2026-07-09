# Project Conventions

## Branching Strategy

```
main        — production-ready, merged only from develop
develop     — integration branch, all feature branches merge here
feature/    — one branch per person or feature
fix/        — bug fixes
```

**Rules:**
- Branch off develop: `git checkout -b feature/fr2-crud develop`
- No direct commits to `main` or `develop`
- Create a Pull Request to merge feature branches into `develop`
- Merge `develop` into `main` only when stable

**Branch naming examples:**
- `feature/fr1-db-sdk`
- `feature/fr2-product-crud`
- `feature/fr3-stock-movement`
- `feature/fr4-reports`
- `feature/fr5-reports`
- `feature/fr6-audit-utils`
- `fix/stock-out-negative-qty`
- `fix/search-crash-empty`

---

## Naming Conventions

| Category | Convention | Examples |
|----------|-----------|----------|
| Variables | camelCase | `productCount`, `maxProducts`, `currentQty`, `searchTerm` |
| Functions | camelCase | `addProduct()`, `stockIn()`, `db_getProduct()`, `getIntInput()` |
| Structs | PascalCase | `Product`, `TransactionLog` |
| Constants | UPPER_SNAKE | `MAX_PRODUCTS`, `NAME_LEN`, `CODE_LEN`, `CODE_PREFIX` |
| Header guards | UPPER_SNAKE | `FILE_DB_H`, `UTILS_H`, `FEATURES_H` |
| File names | snake_case | `file_db.c`, `utils.h`, `features.c` |

**Why camelCase for variables and functions?**
- Consistent with our existing function names
- Common in modern C projects
- Avoids mixing styles in the same codebase

---

## Commit Convention

Format: `<type>(<scope>): <imperative description>`

| Type | When to use |
|------|-------------|
| `feat` | New feature or function |
| `fix` | Bug fix |
| `docs` | Documentation changes |
| `refactor` | Code restructuring with no behavior change |
| `style` | Formatting, indentation, whitespace |
| `chore` | Build system, config files, gitignore |

**Examples:**
```
feat(db): add product insert and get by code
feat(stock): implement stock out with quantity validation
fix(stock): prevent negative quantity on stock out
fix(search): handle empty search term gracefully
docs(readme): add branching strategy and team roles
refactor(input): extract shared validation helpers
style(indent): fix inconsistent indentation
chore(build): add Makefile and CMakeLists.txt
```

**Rules:**
- Use imperative mood (add, fix, implement — not added, fixed, implemented)
- Capitalize the first word after the scope
- No period at the end
- Keep the subject under 72 characters when possible

---

## Code Formatting

| Rule | Standard |
|------|----------|
| Indentation | 4 spaces (no tabs) |
| Braces | K&R style (opening brace on same line as statement) |
| Max line length | 80 characters |
| Comments | Only where logic is non-obvious |
| Includes | Standard headers first, then project headers |
| Memory | No dynamic allocation (use fixed-size arrays) |

**Example:**
```c
int getProductCount() {
    FILE *fp = fopen("inventory.dat", "rb");
    if (fp == NULL) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return (int)(size / sizeof(Product));
}
```

---

## Error Handling

- Check return values of all file operations (fopen, fwrite, fread, fclose)
- Validate all user input before processing
- Return meaningful error codes from functions (0 for failure, 1 for success)
- Print descriptive error messages to the user

---

## File Organization

- `.h` files: struct definitions, constants, function prototypes
- `.c` files: function implementations
- Source code in root directory (except main.c which is in `src/`)
- Build output in `build/` directory (for CMake builds)
- Data files (inventory.dat, transactions.log) generated at runtime
