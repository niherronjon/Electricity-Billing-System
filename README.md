# Electricity-Billing-System

# Project Objectives:
To automate the process of calculating electricity bills based on meter readings.
To manage customer information and billing records efficiently.
To minimize human errors and improve accuracy in the billing process.
To securely store and retrieve consumer data using file handling in C.
To provide an easy way for administrators to manage, update, and generate bills.
System Features:
Customer Management: Add, update, and delete customer records.
Meter Reading Entry: Record previous and current readings for each billing cycle.
Automatic Bill Calculation: Compute total units consumed and calculate bill amount using tariff
rates.
Tariff Management: Apply different rates, discounts, or surcharges based on usage type
(domestic/commercial).
File Handling: Save and retrieve all billing data for future use.
Bill Generation: Display or print bill summaries for each customer.
Functional Requirements:
Requirement ID Functional Requirement Description
FR-01 FR-02 FR-03 FR-04 FR-05 FR-06 FR-07 FR-08 The system shall allow adding new customer details.
The system shall record and update meter readings.
The system shall automatically calculate total electricity units
consumed.
The system shall compute total bill amount using predefined tariff
rates.
The system shall store customer and billing information in files.
The system shall generate and display monthly bills.
The system shall apply discounts, surcharges, or penalties as per
category.
The system shall allow searching and retrieving customer billing
history.
Non-Functional Requirements:
Aspect Description
Performance The system should process billing calculations within seconds for any
customer.
Usability The system should have a simple text-based interface for easy interaction.
Reliability Data stored in files should remain consistent and retrievable without loss.
Portability The program should run on any platform supporting C (Windows/Linux).
Security Customer data should be stored safely with limited access for
administrators.
Use Case Diagram:
Actors:
Administrator (main user managing customers and billing)
Use Cases:
Add/Update/Delete Customer
Enter Meter Reading
Calculate Bill
Generate Bill Report
Retrieve Customer Data
Use Case Descriptions:
Overview
This use case diagram represents an online bill payment system involving two primary actors:
User and Admin. The system enables users to register, log in, check bills, provide service
numbers, pay bills, and receive alerts for payment. The Admin oversees and manages login
access, billing, and payment alerts.
Actors
1. User: The person who registers in the system, checks bills, and makes payments.
2. Admin: The system administrator who manages user logins, billing information, and payment
alerts.
Use Cases
Registration
The user registers by providing necessary details to create an account in the system.
Login
Both user and admin can log in to the system using valid credentials.
Check Bill
The user checks the bill details provided by the admin.
Provide Service No
The user provides the service number to fetch the specific bill details.
Pay Bill
The user pays the bill through the system after verifying the bill amount.
Alert for Payment
The system sends an alert to the user and admin regarding upcoming or due payments.
Relationships
• The User interacts with the system for all main functionalities including registration, login, and
payment.
alerts.
• The Admin monitors user activities and handles login validation, bill updates, and payment
• Both actors are linked through shared actions like Login and Alert for Payment.
System Requirements Specification (SRS)
Summary Table:
Requirement ID Requirement Description Stakeholders
SRS-01 The system must manage customer and meter data. Administrator
SRS-02 The system must automatically calculate bills. Administrator
SRS-03 The system must save and retrieve data using files. Administrator
SRS-04 The system must generate and display bills. Administrator
SRS-05 The system should support both domestic and
commercial rates.
Administrator
Tools and Technologies:
Programming Language: C
Compiler: GCC / Turbo C
IDE: CodeBlocks / Dev C++
Data Storage: File handling in C (text file-based storage)
Platform: Windows or Linux
Conclusion:
The Electricity Billing System provides an efficient, automated solution for managing consumer
data and generating electricity bills. It reduces human errors, ensures faster billing, and maintains
permanent customer records through file handling. This project also enhances understanding of C
programming concepts such as structures, functions, conditional logic, and file operations,
helping students develop strong problem-solving and analytical skills. Ultimately, it
demonstrates how programming can simplify real-world administrative tasks in utility
management systems.
](https://docs.google.com/document/d/1-fYWwMux65qgknTspUM_HFbQNnFzjZ17xWdPWEC8uDI/edit?usp=drivesdk)
