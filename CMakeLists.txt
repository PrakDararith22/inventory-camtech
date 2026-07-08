cmake_minimum_required(VERSION 3.10)
project(InventorySystem C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(inventory
    src/main.c
    src/fileio.c
    src/utils.c
    src/add_product.c
    src/stock.c
    src/search.c
    src/reports.c
    src/audit.c
)
