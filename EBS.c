#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CUSTOMERS 100
#define FILENAME "customers.dat"
#define BILL_FILENAME "bills.dat"
#define ADMIN_FILENAME "admin.dat"

// Structure for Customer Information
typedef struct {
    int customerID;
    char name[50];
    char address[100];
    char phoneNumber[15];
    char customerType[20]; // Domestic or Commercial
    int isActive;
} Customer;

// Structure for Billing Information
typedef struct {
    int customerID;
    int billID;
    int previousReading;
    int currentReading;
    int unitsConsumed;
    float billAmount;
    char billingMonth[20];
    char paymentStatus[20];
} Bill;

// Structure for Admin (Username & Password)
typedef struct {
    char username[20];
    char password[20];
} Admin;

// Global variables
Customer customers[MAX_CUSTOMERS];
int customerCount = 0;
int nextCustomerID = 1001;
int nextBillID = 5001;

Admin admin;          // stores current admin credentials
int adminExists = 0;  // flag to know if admin credentials are loaded

// Function Prototypes
void mainMenu();
void adminLogin();
void customerManagementMenu();
void billingMenu();
void addCustomer();
void viewAllCustomers();
void searchCustomer();
void updateCustomer();
void deleteCustomer();
void enterMeterReading();
void calculateBill(Bill *bill, char *customerType);
void generateBillReport();
void viewBillingHistory();
void payBill(); // NEW: Bill payment function
void saveCustomersToFile();
void loadCustomersFromFile();
void saveBillToFile(Bill bill);
void clearInputBuffer();
int findCustomerByID(int id);
void displayCustomer(Customer c);
void displayBill(Bill b);

// New functions for admin username/password
void loadAdminFromFile();
void saveAdminToFile();
void setupAdminAccount();
void changeAdminCredentials();

// Main Function
int main() {
    loadCustomersFromFile();
    loadAdminFromFile();

    // If no admin account exists yet, force user to create one
    if (!adminExists) {
        setupAdminAccount();
    }

    mainMenu();
    return 0;
}

// Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Load Admin from File
void loadAdminFromFile() {
    FILE *fp = fopen(ADMIN_FILENAME, "rb");
    if (fp == NULL) {
        adminExists = 0;
        return; // No admin file yet
    }

    if (fread(&admin, sizeof(Admin), 1, fp) == 1) {
        adminExists = 1;
    } else {
        adminExists = 0;
    }

    fclose(fp);
}

// Save Admin to File
void saveAdminToFile() {
    FILE *fp = fopen(ADMIN_FILENAME, "wb");
    if (fp == NULL) {
        printf("Error opening admin file for writing!\n");
        return;
    }

    fwrite(&admin, sizeof(Admin), 1, fp);
    fclose(fp);
}

// Setup Admin Account (if none exists)
void setupAdminAccount() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("            INITIAL ADMIN SETUP\n");
    printf("====================================================\n");
    printf("\nNo admin account found.\n");
    printf("Please create an admin username and password.\n\n");

    printf("Enter new admin username (no spaces, max 19 chars): ");
    scanf("%19s", admin.username);
    clearInputBuffer();

    printf("Enter new admin password (no spaces, max 19 chars): ");
    scanf("%19s", admin.password);
    clearInputBuffer();

    saveAdminToFile();
    adminExists = 1;

    printf("\nAdmin account created successfully!\n");
    printf("Username: %s\n", admin.username);
    printf("====================================================\n");
    printf("Press Enter to continue...");
    getchar();
}

// Main Menu
void mainMenu() {
    int choice;

    while (1) {
        system("clear || cls");
        printf("\n");
        printf("====================================================\n");
        printf("        ELECTRICITY BILLING SYSTEM\n");
        printf("====================================================\n");
        printf("\n");
        printf("1. Admin Login\n");
        printf("2. Exit\n");
        printf("\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            printf("Press Enter to continue...");
            getchar();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                saveCustomersToFile();
                printf("\nThank you for using Electricity Billing System!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
                printf("Press Enter to continue...");
                getchar();
        }
    }
}

// Admin Login
void adminLogin() {
    if (!adminExists) {
        printf("\nNo admin account exists! Please restart the program.\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    char username[20], password[20];
    int attempts = 3;

    while (attempts > 0) {
        system("clear || cls");
        printf("\n");
        printf("====================================================\n");
        printf("              ADMIN LOGIN\n");
        printf("====================================================\n");
        printf("\n");
        printf("Username: ");
        scanf("%19s", username);
        printf("Password: ");
        scanf("%19s", password);
        clearInputBuffer();

        if (strcmp(username, admin.username) == 0 &&
            strcmp(password, admin.password) == 0) {
            printf("\nLogin Successful!\n");
            printf("Press Enter to continue...");
            getchar();
            customerManagementMenu();
            return;
        } else {
            attempts--;
            printf("\nInvalid credentials! Attempts remaining: %d\n", attempts);
            if (attempts > 0) {
                printf("Press Enter to try again...");
                getchar();
            }
        }
    }

    printf("\nToo many failed attempts! Returning to main menu...\n");
    printf("Press Enter to continue...");
    getchar();
}

// Change Admin Credentials
void changeAdminCredentials() {
    char currentPassword[20];

    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("      CHANGE ADMIN USERNAME/PASSWORD\n");
    printf("====================================================\n");
    printf("\n");

    printf("Enter current admin password: ");
    scanf("%19s", currentPassword);
    clearInputBuffer();

    if (strcmp(currentPassword, admin.password) != 0) {
        printf("\nIncorrect password! Cannot change credentials.\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    printf("\nEnter new admin username (no spaces, max 19 chars): ");
    scanf("%19s", admin.username);
    clearInputBuffer();

    printf("Enter new admin password (no spaces, max 19 chars): ");
    scanf("%19s", admin.password);
    clearInputBuffer();

    saveAdminToFile();

    printf("\nAdmin credentials updated successfully!\n");
    printf("Press Enter to continue...");
    getchar();
}

// Customer Management Menu
void customerManagementMenu() {
    int choice;

    while (1) {
        system("clear || cls");
        printf("\n");
        printf("====================================================\n");
        printf("        CUSTOMER MANAGEMENT SYSTEM\n");
        printf("====================================================\n");
        printf("\n");
        printf("1. Add New Customer\n");
        printf("2. View All Customers\n");
        printf("3. Search Customer\n");
        printf("4. Update Customer\n");
        printf("5. Delete Customer\n");
        printf("6. Billing Menu\n");
        printf("7. Change Admin Username/Password\n");
        printf("8. Logout\n");
        printf("\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            printf("Press Enter to continue...");
            getchar();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                viewAllCustomers();
                break;
            case 3:
                searchCustomer();
                break;
            case 4:
                updateCustomer();
                break;
            case 5:
                deleteCustomer();
                break;
            case 6:
                billingMenu();
                break;
            case 7:
                changeAdminCredentials();
                break;
            case 8:
                saveCustomersToFile();
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
                printf("Press Enter to continue...");
                getchar();
        }
    }
}

// Billing Menu
void billingMenu() {
    int choice;

    while (1) {
        system("clear || cls");
        printf("\n");
        printf("====================================================\n");
        printf("            BILLING MANAGEMENT\n");
        printf("====================================================\n");
        printf("\n");
        printf("1. Enter Meter Reading & Generate Bill\n");
        printf("2. View Billing History (All Bills)\n");
        printf("3. Generate Bill Report (By Customer)\n");
        printf("4. Pay Bill\n"); // NEW menu option
        printf("5. Back to Main Menu\n");
        printf("\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            printf("Press Enter to continue...");
            getchar();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                enterMeterReading();
                break;
            case 2:
                viewBillingHistory();
                break;
            case 3:
                generateBillReport();
                break;
            case 4:
                payBill();
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
                printf("Press Enter to continue...");
                getchar();
        }
    }
}

// Add New Customer
void addCustomer() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("           ADD NEW CUSTOMER\n");
    printf("====================================================\n");
    printf("\n");

    if (customerCount >= MAX_CUSTOMERS) {
        printf("Customer database is full!\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    Customer newCustomer;
    newCustomer.customerID = nextCustomerID++;
    newCustomer.isActive = 1;

    printf("Customer ID: %d (Auto-generated)\n\n", newCustomer.customerID);

    printf("Enter Customer Name: ");
    fgets(newCustomer.name, sizeof(newCustomer.name), stdin);
    newCustomer.name[strcspn(newCustomer.name, "\n")] = 0;

    printf("Enter Address: ");
    fgets(newCustomer.address, sizeof(newCustomer.address), stdin);
    newCustomer.address[strcspn(newCustomer.address, "\n")] = 0;

    printf("Enter Phone Number: ");
    fgets(newCustomer.phoneNumber, sizeof(newCustomer.phoneNumber), stdin);
    newCustomer.phoneNumber[strcspn(newCustomer.phoneNumber, "\n")] = 0;

    int typeChoice;
    printf("\nCustomer Type:\n");
    printf("1. Domestic\n");
    printf("2. Commercial\n");
    printf("Enter choice: ");
    scanf("%d", &typeChoice);
    clearInputBuffer();

    if (typeChoice == 1) {
        strcpy(newCustomer.customerType, "Domestic");
    } else if (typeChoice == 2) {
        strcpy(newCustomer.customerType, "Commercial");
    } else {
        strcpy(newCustomer.customerType, "Domestic");
    }

    customers[customerCount++] = newCustomer;
    saveCustomersToFile();

    printf("\n====================================================\n");
    printf("Customer added successfully!\n");
    printf("Customer ID: %d\n", newCustomer.customerID);
    printf("====================================================\n");
    printf("\nPress Enter to continue...");
    getchar();
}

// View All Customers
void viewAllCustomers() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("           ALL CUSTOMERS\n");
    printf("====================================================\n");
    printf("\n");

    if (customerCount == 0) {
        printf("No customers found in the system.\n");
        printf("\nPress Enter to continue...");
        getchar();
        return;
    }

    int activeCount = 0;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].isActive) {
            displayCustomer(customers[i]);
            printf("----------------------------------------------------\n");
            activeCount++;
        }
    }

    printf("\nTotal Active Customers: %d\n", activeCount);
    printf("\nPress Enter to continue...");
    getchar();
}

// Search Customer
void searchCustomer() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("           SEARCH CUSTOMER\n");
    printf("====================================================\n");
    printf("\n");

    int searchID;
    printf("Enter Customer ID to search: ");
    scanf("%d", &searchID);
    clearInputBuffer();

    int index = findCustomerByID(searchID);

    if (index != -1 && customers[index].isActive) {
        printf("\n");
        displayCustomer(customers[index]);
    } else {
        printf("\nCustomer not found!\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

// Update Customer
void updateCustomer() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("           UPDATE CUSTOMER\n");
    printf("====================================================\n");
    printf("\n");

    int updateID;
    printf("Enter Customer ID to update: ");
    scanf("%d", &updateID);
    clearInputBuffer();

    int index = findCustomerByID(updateID);

    if (index != -1 && customers[index].isActive) {
        printf("\nCurrent Details:\n");
        displayCustomer(customers[index]);

        printf("\n\nEnter New Details:\n");
        printf("Enter Customer Name: ");
        fgets(customers[index].name, sizeof(customers[index].name), stdin);
        customers[index].name[strcspn(customers[index].name, "\n")] = 0;

        printf("Enter Address: ");
        fgets(customers[index].address, sizeof(customers[index].address), stdin);
        customers[index].address[strcspn(customers[index].address, "\n")] = 0;

        printf("Enter Phone Number: ");
        fgets(customers[index].phoneNumber, sizeof(customers[index].phoneNumber), stdin);
        customers[index].phoneNumber[strcspn(customers[index].phoneNumber, "\n")] = 0;

        int typeChoice;
        printf("\nCustomer Type:\n");
        printf("1. Domestic\n");
        printf("2. Commercial\n");
        printf("Enter choice: ");
        scanf("%d", &typeChoice);
        clearInputBuffer();

        if (typeChoice == 1) {
            strcpy(customers[index].customerType, "Domestic");
        } else if (typeChoice == 2) {
            strcpy(customers[index].customerType, "Commercial");
        }

        saveCustomersToFile();
        printf("\nCustomer updated successfully!\n");
    } else {
        printf("\nCustomer not found!\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

// Delete Customer
void deleteCustomer() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("           DELETE CUSTOMER\n");
    printf("====================================================\n");
    printf("\n");

    int deleteID;
    printf("Enter Customer ID to delete: ");
    scanf("%d", &deleteID);
    clearInputBuffer();

    int index = findCustomerByID(deleteID);

    if (index != -1 && customers[index].isActive) {
        displayCustomer(customers[index]);

        char confirm;
        printf("\nAre you sure you want to delete this customer? (y/n): ");
        scanf("%c", &confirm);
        clearInputBuffer();

        if (confirm == 'y' || confirm == 'Y') {
            customers[index].isActive = 0;
            saveCustomersToFile();
            printf("\nCustomer deleted successfully!\n");
        } else {
            printf("\nDeletion cancelled.\n");
        }
    } else {
        printf("\nCustomer not found!\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

// Enter Meter Reading and Generate Bill
void enterMeterReading() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("      ENTER METER READING & GENERATE BILL\n");
    printf("====================================================\n");
    printf("\n");

    int custID;
    printf("Enter Customer ID: ");
    scanf("%d", &custID);
    clearInputBuffer();

    int index = findCustomerByID(custID);

    if (index == -1 || !customers[index].isActive) {
        printf("\nCustomer not found!\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    printf("\nCustomer Details:\n");
    displayCustomer(customers[index]);

    Bill newBill;
    newBill.customerID = custID;
    newBill.billID = nextBillID++;

    printf("\n\nEnter Billing Month (e.g., January 2025): ");
    fgets(newBill.billingMonth, sizeof(newBill.billingMonth), stdin);
    newBill.billingMonth[strcspn(newBill.billingMonth, "\n")] = 0;

    printf("Enter Previous Meter Reading: ");
    scanf("%d", &newBill.previousReading);

    printf("Enter Current Meter Reading: ");
    scanf("%d", &newBill.currentReading);
    clearInputBuffer();

    if (newBill.currentReading < newBill.previousReading) {
        printf("\nError: Current reading cannot be less than previous reading!\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    newBill.unitsConsumed = newBill.currentReading - newBill.previousReading;
    calculateBill(&newBill, customers[index].customerType);
    strcpy(newBill.paymentStatus, "Unpaid");

    saveBillToFile(newBill);

    printf("\n");
    printf("====================================================\n");
    printf("           BILL GENERATED SUCCESSFULLY\n");
    printf("====================================================\n");
    displayBill(newBill);

    printf("\nPress Enter to continue...");
    getchar();
}

// Calculate Bill based on tariff rates
void calculateBill(Bill *bill, char *customerType) {
    float amount = 0.0f;
    int units = bill->unitsConsumed;

    if (strcmp(customerType, "Domestic") == 0) {
        // Domestic Tariff Structure
        if (units <= 50) {
            amount = units * 3.50f;
        } else if (units <= 150) {
            amount = 50 * 3.50f + (units - 50) * 4.00f;
        } else if (units <= 250) {
            amount = 50 * 3.50f + 100 * 4.00f + (units - 150) * 5.20f;
        } else {
            amount = 50 * 3.50f + 100 * 4.00f + 100 * 5.20f + (units - 250) * 6.50f;
        }
    } else {
        // Commercial Tariff Structure (higher rates)
        if (units <= 100) {
            amount = units * 7.50f;
        } else if (units <= 300) {
            amount = 100 * 7.50f + (units - 100) * 8.50f;
        } else {
            amount = 100 * 7.50f + 200 * 8.50f + (units - 300) * 10.00f;
        }
    }

    // Apply surcharge for high consumption (above 500 units)
    if (units > 500) {
        amount += amount * 0.10f; // 10% surcharge
    }

    // Apply discount for low consumption (below 50 units for domestic)
    if (strcmp(customerType, "Domestic") == 0 && units < 50) {
        amount -= amount * 0.05f; // 5% discount
    }

    bill->billAmount = amount;
}

// Generate Bill Report (by Customer ID)
void generateBillReport() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("           GENERATE BILL REPORT\n");
    printf("====================================================\n");
    printf("\n");

    int custID;
    printf("Enter Customer ID: ");
    scanf("%d", &custID);
    clearInputBuffer();

    int index = findCustomerByID(custID);

    if (index == -1 || !customers[index].isActive) {
        printf("\nCustomer not found!\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    FILE *fp = fopen(BILL_FILENAME, "rb");
    if (fp == NULL) {
        printf("\nNo billing records found!\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    Bill bill;
    int found = 0;

    printf("\nBilling History for Customer ID: %d\n", custID);
    printf("Customer Name: %s\n", customers[index].name);
    printf("\n====================================================\n");

    while (fread(&bill, sizeof(Bill), 1, fp)) {
        if (bill.customerID == custID) {
            displayBill(bill);
            printf("----------------------------------------------------\n");
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nNo billing records found for this customer!\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

// View Billing History (All Bills)
void viewBillingHistory() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("           BILLING HISTORY\n");
    printf("====================================================\n");
    printf("\n");

    FILE *fp = fopen(BILL_FILENAME, "rb");
    if (fp == NULL) {
        printf("No billing records found!\n");
        printf("\nPress Enter to continue...");
        getchar();
        return;
    }

    Bill bill;
    int count = 0;

    while (fread(&bill, sizeof(Bill), 1, fp)) {
        displayBill(bill);
        printf("----------------------------------------------------\n");
        count++;
    }

    fclose(fp);

    printf("\nTotal Bills: %d\n", count);
    printf("\nPress Enter to continue...");
    getchar();
}

// NEW: Pay Bill
void payBill() {
    system("clear || cls");
    printf("\n");
    printf("====================================================\n");
    printf("                 PAY BILL\n");
    printf("====================================================\n");
    printf("\n");

    int billID;
    printf("Enter Bill ID to pay: ");
    if (scanf("%d", &billID) != 1) {
        clearInputBuffer();
        printf("\nInvalid input!\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }
    clearInputBuffer();

    FILE *fp = fopen(BILL_FILENAME, "rb+");
    if (fp == NULL) {
        printf("\nNo billing records found!\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    Bill bill;
    int found = 0;

    while (fread(&bill, sizeof(Bill), 1, fp)) {
        if (bill.billID == billID) {
            found = 1;
            printf("\nBill Details:\n");
            displayBill(bill);

            if (strcmp(bill.paymentStatus, "Paid") == 0) {
                printf("\nThis bill is already marked as PAID.\n");
                fclose(fp);
                printf("\nPress Enter to continue...");
                getchar();
                return;
            }

            char confirm;
            printf("\nConfirm payment of this bill? (y/n): ");
            scanf(" %c", &confirm);
            clearInputBuffer();

            if (confirm == 'y' || confirm == 'Y') {
                strcpy(bill.paymentStatus, "Paid");

                // Move file pointer back one record to overwrite the current bill
                fseek(fp, -(long)sizeof(Bill), SEEK_CUR);
                fwrite(&bill, sizeof(Bill), 1, fp);
                fflush(fp);

                printf("\nBill payment successful! Status updated to PAID.\n");
            } else {
                printf("\nPayment cancelled.\n");
            }

            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nBill with ID %d not found!\n", billID);
    }

    printf("\nPress Enter to continue...");
    getchar();
}

// Save Customers to File
void saveCustomersToFile() {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fwrite(&customerCount, sizeof(int), 1, fp);
    fwrite(&nextCustomerID, sizeof(int), 1, fp);
    fwrite(customers, sizeof(Customer), customerCount, fp);

    fclose(fp);
}

// Load Customers from File
void loadCustomersFromFile() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        return; // File doesn't exist yet
    }

    fread(&customerCount, sizeof(int), 1, fp);
    fread(&nextCustomerID, sizeof(int), 1, fp);
    fread(customers, sizeof(Customer), customerCount, fp);

    fclose(fp);
}

// Save a Single Bill to File
void saveBillToFile(Bill bill) {
    FILE *fp = fopen(BILL_FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening bill file for writing!\n");
        return;
    }

    fwrite(&bill, sizeof(Bill), 1, fp);
    fclose(fp);
}

// Find Customer Index by ID
int findCustomerByID(int id) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].customerID == id) {
            return i;
        }
    }
    return -1;
}

// Display Customer Info
void displayCustomer(Customer c) {
    printf("Customer ID      : %d\n", c.customerID);
    printf("Name             : %s\n", c.name);
    printf("Address          : %s\n", c.address);
    printf("Phone Number     : %s\n", c.phoneNumber);
    printf("Customer Type    : %s\n", c.customerType);
    printf("Status           : %s\n", c.isActive ? "Active" : "Inactive");
}

// Display Bill Info
void displayBill(Bill b) {
    printf("Bill ID          : %d\n", b.billID);
    printf("Customer ID      : %d\n", b.customerID);
    printf("Billing Month    : %s\n", b.billingMonth);
    printf("Previous Reading : %d units\n", b.previousReading);
    printf("Current Reading  : %d units\n", b.currentReading);
    printf("Units Consumed   : %d units\n", b.unitsConsumed);
    printf("Bill Amount      : $%.2f\n", b.billAmount);
    printf("Payment Status   : %s\n", b.paymentStatus);
}
