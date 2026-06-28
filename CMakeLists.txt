cmake_minimum_required(VERSION 3.10)
project(InventorySystem C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(inventory
    src/main.c
    file_db.c
    features.c
)
