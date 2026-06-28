#include <ctype.h>
#include <stdio.h>
#include <string.h>

void displayMenu();

int main() {
  int choice;
  do {
    displayMenu();
    scanf("%d", &choice);
    while (getchar() != '\n')
      ;

    switch (choice) {
    case 1:
      printf("\n--- Add Product ---\n");
      break;
    case 2:
      printf("\n--- Stock In ---\n");
      break;

    case 3:
      printf("\n--- Stock Out ---\n");
      break;

    case 4:
      printf("\n--- Search Product ---\n");
      break;

    case 5:
      printf("\n--- Low Stock Report ---\n");
      break;

    case 6:
      printf("\n--- Inventory Value ---\n");
      break;

    case 7:
      printf("\n--- View Audit Log ---\n");
      break;

    case 8:
      printf("Exiting... Goodbye!\n");
      break;

    default:
      printf("Invalid choice. Enter 1-8.\n");
    }
  } while (choice != 8);

  return 0;
}
void displayMenu() {
  printf("\n====================================\n");
  printf("  INVENTORY MANAGEMENT SYSTEM\n");
  printf("         - CAMTECH -\n");
  printf("====================================\n");
  printf("1. Add Product\n");
  printf("2. Stock In\n");
  printf("3. Stock Out\n");
  printf("4. Search Product\n");
  printf("5. Low Stock Report\n");
  printf("6. Inventory Value\n");
  printf("7. View Audit Log\n");
  printf("8. Exit\n");
  printf("------------------------------------\n");
  printf("Enter your choice: ");
}
