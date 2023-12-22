# BillDesk 🧾💻

BillDesk is a simple billing software implemented in C. It allows users to create bills, search for existing bills, edit product details, and print invoices for Fresh Mart, a retail store located in Mumbai, Maharashtra,India providing high-quality groceries, fresh produce, and household essentials to its customers.

## Demo Video 🎥

https://github.com/meet244/BillDesk/assets/83262693/5bbcdfb0-8a75-492a-8288-60ab62b199d4

## Features ✨

- Creating bills: Users can create bills by selecting items from a product list and entering the quantity. The software automatically calculates the total price and generates a bill with GST breakup.
- Searching bills: Users can search for bills by entering the bill number. The software displays the bill details if found.
- Editing product details: Users can edit the name, price, and stock of existing products in the product list.
- Printing invoices: Users can print invoices with a unique bill number, store details, item details, and payment information.

## Getting Started 🚀

To run the BillDesk software, follow these steps:

1. Clone the repository: `git clone <repository_url>`
2. Compile the code: `gcc billdesk.c -o billdesk`
3. Run the program: `./billdesk`

## Usage 📝

1. When the program starts, a menu will be displayed with the following options:
   - 0: Print bill
   - 1: Search bill
   - 2: Edit items
   - 3: Exit

2. Select an option by entering the corresponding number.

3. If you choose to print a bill, you will be prompted to enter the item codes and quantities. Once done, the program will generate a bill and save it in the "Cmini" folder.

4. If you choose to search a bill, enter the bill number to retrieve and display the bill details.

5. If you choose to edit items, you can modify the name, price, and stock of existing products in the product list.

6. Exiting the program will terminate the software.

## Requirements 🛠️

- C compiler
- Windows operating system

## Authors 👥

- Meet Patel
- Harshil Damania
