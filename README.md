⚡ Electricity Billing System (C Language)

A console-based Electricity Billing System developed in C, designed to manage customers, generate electricity bills, handle payments, and secure access through an admin login system.
The application uses file handling to ensure data persistence across program executions.


 📌 Features Overview
 
🔐 Admin Management

Secure admin login with username and password

First-run admin setup if no credentials exist

Option to change admin username and password

Limited login attempts for security



👥 Customer Management

Add new customers (Domestic or Commercial)

Auto-generated Customer IDs

View all active customers

Search customer by ID

Update customer details

Soft delete customers (inactive instead of permanent removal)


💡 Billing Management

Enter meter readings and generate bills

Auto-calculated electricity charges based on tariff slabs

Separate billing logic for Domestic and Commercial customers

Monthly billing support

Automatic unit consumption calculation



💰 Payment System

View unpaid and paid bills

Pay bills using Bill ID

Payment status updates stored permanently

📊 Reports & History

View complete billing history

Generate billing reports for a specific customer

Persistent bill storage using binary files

🛠️ Technologies Used

Programming Language: C

Concepts Applied:

Structures

File Handling (Binary files)

Modular Programming

Input Validation

Menu-driven UI

Compiler: GCC / Any standard C compiler
