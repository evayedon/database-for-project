#include <iostream>
#include <string>
#include <sqlite3.h>
#include <limits>
#include <iomanip>
#include <regex>

using namespace std;

void printMainMenu();
int mainMenu();
void addRecord(sqlite3 *);
// sub-menu for addRecord
void addCustomer(sqlite3 *);
void addProduct(sqlite3 *);
void addSale(sqlite3 *);
void addCustomer(sqlite3 *);
void addTournament(sqlite3 *);
void addSaleItem(sqlite3 *);
void addTournamentRegistration(sqlite3 *);

void updateRecord(sqlite3 *);
// sub-menu for update record
void updateProduct(sqlite3 *);
void updateSale(sqlite3 *);
void updateCustomer(sqlite3 *);
void updateTournament(sqlite3 *);
void updateSaleItem(sqlite3 *);
void updateTournamentRegistration(sqlite3 *);

void deleteRecord(sqlite3 *);
void deleteProduct(sqlite3 *);
void deleteSale(sqlite3 *);
void deleteCustomer(sqlite3 *);
void deleteTournament(sqlite3 *);
void deleteSaleItem(sqlite3 *);
void deleteTournamentRegistration(sqlite3 *);

void recordTransaction(sqlite3 *);
void viewSale(sqlite3 *);
void viewCustomer(sqlite3 *);
void viewProduct(sqlite3 *);
void printPage(sqlite3_stmt *, int, int);

// Get and validate user choice
int getValidatedChoice();
int getValidatedChoice(int, int, int = -1);
string getDateTimeFromUser();
void startPage(sqlite3 *);
bool deleteHelper(sqlite3 *, const string &, const string &,
                  const string &, int = 1, int = 9999);



int main()
{
    int choice;

    sqlite3 *mydb;

    int rc = sqlite3_open_v2("gameZone.db", &mydb, SQLITE_OPEN_READWRITE, NULL);

    cout << "Welcome to GameZone" << endl;
    startPage(mydb);
    sqlite3_close(mydb);
    return 0;
}

void startPage(sqlite3 *mydb)
{
    int choice = 0; 

    while (true)
    {
        choice = mainMenu();

        switch (choice)
        {
        case 1:
            addRecord(mydb);
            break;
        case 2:
            updateRecord(mydb);
            break;
        case 3:
            deleteRecord(mydb);
            break;
        case -1:
            cout << "Exiting program..." << endl;
            return; // exits the function (and loop)
        default:
            cout << "That is not a valid choice. Please try again." << endl;
            break;
        }
    }
}

// print main meu
void printMainMenu()
{
    cout << "Please choose an option (enter -1 to quit):  " << endl;
    cout << "1. Add Record" << endl;
    cout << "2. Update Record" << endl;
    cout << "3. Delete Record" << endl;
}

// main menu
int mainMenu()
{

    printMainMenu();
    cout << "Enter Choice: ";
    int choice = getValidatedChoice(1, 3);
    return choice;
}

// there are error when running mainmenu() funtion in add, update, and delete

void addRecord(sqlite3 *db)
{
    /*
    == Add Menu Option ==
    -- Choosing this will lead to a sub-menu where you will specify the table to add to.
    -- You should support adding to 2 of your tables.
    -- You should prompt for the information needed to perform the add.
    -- You should not take direct entry of SQL from the user.
    -- This option will be used to add data to 1 table at a time and is separate from the transaction.*/
    cout << "Select table to add record (Enter -1 to go back):" << endl;
    cout << "1. Product" << endl;
    cout << "2. Sale" << endl;
    cout << "3. Customer" << endl;
    cout << "4. Tournament" << endl;
    cout << "5. Sale Item" << endl;
    cout << "6. Tournament Registration" << endl;
    cout << "Enter Choice: ";
    int choice = getValidatedChoice(1, 6);
    switch (choice)
    {
    case 1:
        addProduct(db);
        break;
    case 2:
        addSale(db);
        break;
    case 3:
        addCustomer(db);
        break;
    case 4:
        addTournament(db);
        break;
    case 5:
        addSaleItem(db);
        break;
    case 6:
        addTournamentRegistration(db);
        break;
    case -1:
        startPage(db);
    default:
        cout << "That is not a valid choice." << endl;
        break;
    }
}

void updateRecord(sqlite3 *db)
{
    /*
    == Update Menu Option ==
    -- Choosing this will lead to a sub-menu where you will specify the table to add to.
    -- You should support adding to 2 of your tables.
    -- You should prompt for the information needed to perform the add.
    -- You should not take direct entry of SQL from the user.
    -- This option will be used to add data to 1 table at a time and is separate from the transaction.*/
    cout << "Select table to update record (Enter -1 to go back):" << endl;
    cout << "1. Product" << endl;
    cout << "2. Sale" << endl;
    cout << "3. Customer" << endl;
    cout << "4. Tournament" << endl;
    cout << "5. Sale Item" << endl;
    cout << "6. Tournament Registration" << endl;
    cout << "Enter Choice: ";
    int choice = getValidatedChoice(1, 6);
    switch (choice)
    {
    case 1:
        updateProduct(db);
        break;
    case 2:
        updateSale(db);
        break;
    case 3:
        updateCustomer(db);
        break;
    case 4:
        updateTournament(db);
        break;
    case 5:
        updateSaleItem(db);
        break;
    case 6:
        updateTournamentRegistration(db);
        break;
    case -1:
        startPage(db);
    default:
        cout << "That is not a valid choice." << endl;
        break;
    }
}

void deleteRecord(sqlite3 *db)
{
    /*
    == Delete Menu Option ==
    -- Choosing this will lead to a sub-menu where you will specify the table to add to.
    -- You should support adding to 2 of your tables.
    -- You should prompt for the information needed to perform the add.
    -- You should not take direct entry of SQL from the user.
    -- This option will be used to add data to 1 table at a time and is separate from the transaction.*/
    cout << "Select table to delete record (Enter -1 to go back):" << endl;
    cout << "1. Product" << endl;
    cout << "2. Sale" << endl;
    cout << "3. Customer" << endl;
    cout << "4. Tournament" << endl;
    cout << "5. Sale Item" << endl;
    cout << "6. Tournament Registration" << endl;
    cout << "Enter Choice: ";
    int choice = getValidatedChoice(1, 6);
    switch (choice)
    {
    case 1:
        deleteProduct(db);
        break;
    case 2:
        deleteSale(db);
        break;
    case 3:
        deleteCustomer(db);
        break;
    case 4:
        deleteTournament(db);
        break;
    case 5:
        deleteSaleItem(db);
        break;
    case 6:
        deleteTournamentRegistration(db);
        break;
    case -1:
        startPage(db);
    default:
        cout << "That is not a valid choice." << endl;
        break;
    }
}

void recordTransaction(sqlite3 *db)
{
    /* == 1 transaction menu option that executes multiple SQL statements.==
    -- Transaction example: making a sale
    -- Create a record for the order
    -- Create a record for all products that are a part of the order
    -- Update the inventory to remove products sold
    -- Update the customer to add the order total to their balance.
    -- The selects, inserts, updates, and deletes that make up the transaction do not count for other program requirements.*/
}

// add record
void addProduct(sqlite3 *db)
{
    string p_name;
    double p_price;
    int p_quantity;
    int min_stock_level;
    sqlite3_stmt *stmt;

    cout << "Enter product name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, p_name);
    cout << "Choose the category for the product: " << endl;
    cout << "1. Games" << endl;
    cout << "2. Consoles" << endl;
    cout << "3. Accessories" << endl;
    int category_id = getValidatedChoice(1, 3);

    // input validation for price, quantity, min stock level
    cout << "Enter product price: ";
    cin >> p_price;
    cout << "Enter product quantity: ";
    cin >> p_quantity;
    cout << "Enter minimum stock level: ";
    cin >> min_stock_level;

    string query = "INSERT INTO Product (p_name, category_id, p_price, p_quantity, min_stock_level) "
                   "VALUES (?,?,?,?,?);";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error inserting record: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        sqlite3_bind_text(stmt, 1, p_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, category_id);
        sqlite3_bind_double(stmt, 3, p_price);
        sqlite3_bind_int(stmt, 4, p_quantity);
        sqlite3_bind_int(stmt, 5, min_stock_level);

        result_code = sqlite3_step(stmt);
        if (result_code != SQLITE_DONE)
        {
            cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        }
        else
            cout << "Record inserted successfully." << endl;
    }
    sqlite3_finalize(stmt);
}

void addSale(sqlite3 *db)
{
    string query;
    int cus_id;
    double discount;
    sqlite3_stmt *stmt;
    
    // Choose customer
    query = "SELECT cus_id, cus_fname, cus_lname FROM customer;";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    
    cout << "Choose the Customer for the Sale: " << endl;
    printPage(stmt, 5, 0);
    cus_id = getValidatedChoice(1, 5);
    sqlite3_finalize(stmt);

    cout << "Enter discount applied (0 for none): ";
    discount = getValidatedChoice(0, 100);

        // Payment status
    cout << "Enter payment status:\n";
    cout << "1. Pending\n2. Paid\n3. Unpaid\n4. Cancel\n";
    int payment_status_id = getValidatedChoice(1, 4);

    // Insert sale - 3 placeholders for 3 values (sale_datetime is generated)
    string query1 = "INSERT INTO sale (sale_datetime, cus_id, total_amount, discount_applied, payment_status_id) "
                    "VALUES (datetime('now'), ?, ?, ?,?);";
    result_code = sqlite3_prepare_v2(db, query1.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error inserting record: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, cus_id);
    sqlite3_bind_double(stmt, 2, 0.0);  // Initial total amount
    sqlite3_bind_double(stmt, 3, discount);
    sqlite3_bind_int(stmt, 4, payment_status_id);

    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Record inserted successfully." << endl;
    }
    sqlite3_finalize(stmt);  
}

void addCustomer(sqlite3 *db)
{
    string c_fname;
    string c_lname;
    string c_email;
    string c_phone;
    sqlite3_stmt *stmt;

    // you will have to write a function for input validation
    cout << "Enter customer first name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, c_fname);
    cout << "Enter customer last name: ";
    getline(cin, c_lname);
    cout << "Enter customer email: ";
    getline(cin, c_email);
    cout << "Enter customer phone: ";
    getline(cin, c_phone);
    cout << "Choose membership status: " << endl;
    cout << "1. Non-member" << endl;
    cout << "2. Standard" << endl;
    cout << "3. Premium" << endl;
    int membership_status = getValidatedChoice(1, 3);

    string query = "insert into customer (cus_fname, cus_lname, cus_phone, cus_email, membership_id) "
                   "values (?,?,?,?,?);";

    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error inserting record" << sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_text(stmt, 1, c_fname.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, c_lname.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, c_phone.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, c_email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, membership_status);
    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
    }
    else
        cout << "Record inserted successfully." << endl;

    sqlite3_finalize(stmt);
}

void addTournament(sqlite3 *db)
{
    string t_name;
    string t_date;
    double t_entry_fee;
    int max_players;
    sqlite3_stmt *stmt;

    cout << "Enter tournament name: ";
    getline(cin, t_name).ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter tournament date (YYYY-MM-DD): ";
    getline(cin, t_date);
    cout << "Enter tournament entry fee: ";
    cin >> t_entry_fee;
    cout << "Enter maximum number of players (max player is 16): ";
    max_players = getValidatedChoice(1, 16);

    string query = "insert into tournament (tour_name, tour_datetime, tour_fee, max_players) "
                   "values (?,?,?,?);";
    
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error inserting record" << sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_text(stmt, 1, t_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, t_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, t_entry_fee);
    sqlite3_bind_int(stmt, 4, max_players);

    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error inserting record" << sqlite3_errmsg(db);
    }
    else
        cout << "Record inserted successfully." << endl;
   
    sqlite3_finalize(stmt);
}

void addSaleItem(sqlite3 *db)
{
    string query;
    int sale_id, p_code, quantity;
    double p_price;
    sqlite3_stmt *stmt;
    
    // Choose sale
    query = "SELECT sale_id, cus_fname, cus_lname, sale_datetime "
            "FROM sale JOIN customer ON sale.cus_id = customer.cus_id;";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    
    cout << "Choose the Sale to add item: " << endl;
    printPage(stmt, 5, 0);
    sale_id = getValidatedChoice(1, 5);
    sqlite3_finalize(stmt);
    
    // Choose product
    query = "SELECT p_code, p_name, p_price FROM product;";
    result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    // need to change for more than 5 products
    cout << "Choose the Product to add: " << endl;
    printPage(stmt, 5, 0);
    p_code = getValidatedChoice(1, 5);
    sqlite3_finalize(stmt);
    
    // Get the product price
    query = "SELECT p_price FROM product WHERE p_code = ?;";
    result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error getting product price: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, p_code);
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        p_price = sqlite3_column_double(stmt, 0);
    }
    else
    {
        cout << "Error: Product not found!" << endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);
    
    cout << "Enter quantity: ";
    quantity = getValidatedChoice();
    
    // Calculate item price
    double item_price = quantity * p_price;
    
    // Insert sale item
    query = "INSERT INTO sale_item (sale_id, p_code, quantity, item_price) VALUES (?, ?, ?, ?);";
    result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, sale_id);
    sqlite3_bind_int(stmt, 2, p_code);
    sqlite3_bind_int(stmt, 3, quantity);
    sqlite3_bind_double(stmt, 4, item_price);
    
    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Record inserted successfully." << endl;
        
        // Update the total_amount in the sale table
        string update_query = "UPDATE sale SET total_amount = "
                             "(SELECT SUM(item_price) FROM sale_item WHERE sale_id = ?) "
                             "WHERE sale_id = ?;";
        sqlite3_stmt *update_stmt;
        if (sqlite3_prepare_v2(db, update_query.c_str(), -1, &update_stmt, NULL) == SQLITE_OK)
        {
            sqlite3_bind_int(update_stmt, 1, sale_id);
            sqlite3_bind_int(update_stmt, 2, sale_id);
            sqlite3_step(update_stmt);
            sqlite3_finalize(update_stmt);
        }
    }
    
    sqlite3_finalize(stmt);
}

void addTournamentRegistration(sqlite3 *db)
{
    int tour_id;
    int cus_id;
    sqlite3_stmt *stmt;

    // Choose tournament
    string query = "SELECT tour_id, tour_name FROM tournament;";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK)
    {
        cout << "Error selecting tournaments: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Choose the Tournament to register:\n";
    printPage(stmt, 5, 0);
    cout << "Enter Tournament ID: ";
    tour_id  = getValidatedChoice();
    sqlite3_finalize(stmt);

    // Choose customer
    query = "SELECT cus_id, cus_fname, cus_lname FROM customer;";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK)
    {
        cout << "Error selecting customers: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Choose the Customer to register:\n";
    printPage(stmt, 5, 0);
    cout << "Enter Customer ID: ";
    cus_id = getValidatedChoice();
    sqlite3_finalize(stmt);

    // Payment status
    cout << "Enter payment status:\n";
    cout << "1. Pending\n2. Paid\n3. Unpaid\n4. Cancel\n";
    int payment_status_id = getValidatedChoice(1, 4);

    string query1 = "INSERT INTO tournament_registration "
                    "(tour_id, cus_id, registration_datetime, payment_status_id) "
                    "VALUES (?, ?, datetime('now'), ?);";
    int result_code = sqlite3_prepare_v2(db, query1.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, tour_id);
    sqlite3_bind_int(stmt, 2, cus_id);
    sqlite3_bind_int(stmt, 3, payment_status_id);
 
    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;   
    }
    else
    {
        cout << "Record inserted successfully." << endl;
    }
    sqlite3_finalize(stmt);
}

// update record
void updateProduct(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    
    // Select product
    string query = "SELECT p_code, p_name, p_price FROM product;";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // need to change for more than 5 products
    cout << "Choose the product to update: " << endl;
    printPage(stmt, 5, 0);
    int p_code = getValidatedChoice(1, 5);
    sqlite3_finalize(stmt);

    // Choose field
    cout << "Choose field to update: " << endl;
    cout << "1. Product name" << endl;
    cout << "2. Price" << endl;
    cout << "3. Quantity" << endl;
    cout << "4. Minimum stock level" << endl;
    cout << "5. Product category" << endl;
    cout << "Enter Choice: ";
    int field = getValidatedChoice(1, 5);

    string update_query;
    string column_name;
    
    switch (field)
    {
        case 1: column_name = "p_name"; break;
        case 2: column_name = "p_price"; break;
        case 3: column_name = "p_quantity"; break;
        case 4: column_name = "min_stock_level"; break;
        case 5: column_name = "category_id"; break;
        default:
            cout << "Invalid choice." << endl;
            return;
    }
    
    update_query = "UPDATE product SET " + column_name + " = ? WHERE p_code = ?;";
    result_code = sqlite3_prepare_v2(db, update_query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    switch (field)
    {
        case 1: // Product name
        {
            string new_name;
            cout << "Enter new product name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, new_name);
            sqlite3_bind_text(stmt, 1, new_name.c_str(), -1, SQLITE_TRANSIENT);
            break;
        }
        case 2: // Price
        {
            double price;
            cout << "Enter new price: ";
            cin >> price;
            sqlite3_bind_double(stmt, 1, price);
            break;
        }
        case 3: // Quantity
        {
            cout << "Enter quantity: ";
            int quantity = getValidatedChoice();
            sqlite3_bind_int(stmt, 1, quantity);
            break;
        }
        case 4: // Min stock level
        {
            cout << "Enter minimum stock level: ";
            int min_level = getValidatedChoice();
            sqlite3_bind_int(stmt, 1, min_level);
            break;
        }
        case 5: // Category
        {
            cout << "Choose new category:" << endl;
            cout << "1. Games\n2. Consoles\n3. Accessories" << endl;
            int category = getValidatedChoice(1, 3);
            sqlite3_bind_int(stmt, 1, category);
            break;
        }
    }
    
    sqlite3_bind_int(stmt, 2, p_code);
    
    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Record updated successfully." << endl;
    }
    
    sqlite3_finalize(stmt);
}

void updateSale(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    
    // Select sale
    string query = "SELECT sale_id, customer.cus_id, cus_fname, cus_lname FROM sale JOIN customer on sale.cus_id = customer.cus_id;";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Choose the sale to update: " << endl;
    printPage(stmt, 5, 0);
    int sale_id = getValidatedChoice(1, 5);
    sqlite3_finalize(stmt);

    // Choose field
    cout << "Choose field to update: " << endl;
    cout << "1. Discount applied" << endl;
    cout << "2. Total amount" << endl;
    cout << "3. Payment Status" << endl;
    cout << "Enter Choice: ";
    int field = getValidatedChoice(1, 3);

    string update_query;
    string column_name;
    
    // Determine which column to update
    switch (field)
    {
        case 1: column_name = "discount_applied"; break;
        case 2: column_name = "total_amount"; break;
        case 3: column_name = "payment_status_id"; break;
        default:
            cout << "Invalid choice." << endl;
            return;
    }
    
    update_query = "UPDATE sale SET " + column_name + " = ? WHERE sale_id = ?;";
    result_code = sqlite3_prepare_v2(db, update_query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    switch (field)
    {
        case 1: // Discount applied
        {
            cout << "Enter discount applied: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int discount = getValidatedChoice(0, 100);
            sqlite3_bind_int(stmt, 1, discount);
            break;
        }
        case 2: // Total amount
        {
            double total_amount;
            cout << "Enter total amount: ";
            cin >> total_amount;
            sqlite3_bind_double(stmt, 1, total_amount);
            break;
        }
        case 3: // Payment status
        {
            cout << "Choose new payment status:" << endl;
            cout << "1. Pending\n2. Paid\n3. Unpaid\n4. Cancel" << endl;
            int payment_status = getValidatedChoice(1, 4);
            sqlite3_bind_int(stmt, 1, payment_status);
            break;
        }
    }
    
    sqlite3_bind_int(stmt, 2, sale_id);
    
    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    else
    {
        cout << "Record updated successfully." << endl;
    }
    
    sqlite3_finalize(stmt);
}

void updateCustomer(sqlite3 *db)
{
    string query;
    sqlite3_stmt *stmt;

    // Choose customer
    query = "SELECT cus_id, cus_fname, cus_lname FROM customer;";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    cout << "Choose the Customer to update: " << endl;
    printPage(stmt, 5, 0);
    int cus_id = getValidatedChoice(1, 5);
    sqlite3_finalize(stmt);
    // Choose field
    cout << "Choose field to update: " << endl;
    cout << "1. First name" << endl;
    cout << "2. Last name" << endl;
    cout << "3. Email" << endl;
    cout << "4. Phone" << endl;
    cout << "5. Membership status" << endl;
    int field = getValidatedChoice(1, 5);

    string column_name;
    switch(field)
    {
        case 1: column_name = "cus_fname"; break;
        case 2: column_name = "cus_lname"; break;
        case 3: column_name = "cus_email"; break;
        case 4: column_name = "cus_phone"; break;
        case 5: column_name = "membership_id"; break;
        default:
            cout << "Invalid choice." << endl;
            return;
    }
    string update_query = "UPDATE customer SET " + column_name + " = ? WHERE cus_id = ?;";
    result_code = sqlite3_prepare_v2(db, update_query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    // Bind values based on field type
    switch (field)
    {
        case 1: // First name
            {
                string new_fname;
                cout << "Enter new first name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, new_fname);
                sqlite3_bind_text(stmt, 1, new_fname.c_str(), -1, SQLITE_TRANSIENT);
            }
            break;
        case 2: // Last name
            {
                string new_lname;
                cout << "Enter new last name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, new_lname);
                sqlite3_bind_text(stmt, 1, new_lname.c_str(), -1, SQLITE_TRANSIENT);
            }
            break;
        case 3: // Email
            {
                string new_email;
                cout << "Enter new email: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, new_email);
                sqlite3_bind_text(stmt, 1, new_email.c_str(), -1, SQLITE_TRANSIENT);
            }
            break;
        case 4: // Phone
            {
                string new_phone;
                cout << "Enter new phone: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, new_phone);
                sqlite3_bind_text(stmt, 1, new_phone.c_str(), -1, SQLITE_TRANSIENT);
            }
            break;
        case 5: // Membership status
            {
                cout << "Choose new membership status:" << endl;
                cout << "1. Non-member\n2. Standard\n3. Premium" << endl;
                int membership = getValidatedChoice(1, 3);
                sqlite3_bind_int(stmt, 1, membership);
            }
            break;
        default:
            cout << "Invalid choice." << endl;
            sqlite3_finalize(stmt);
            return;
    }
    sqlite3_bind_int(stmt, 2, cus_id);
    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    else
    {
        cout << "Record updated successfully." << endl;
    }
    sqlite3_finalize(stmt);
}

void updateTournament(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    
    // Select tournament
    string query = "SELECT tour_id, tour_name FROM tournament;";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }

    cout << "Choose the tournament to update: " << endl;
    printPage(stmt, 5, 0);
    int tour_id = getValidatedChoice(1, 5);
    sqlite3_finalize(stmt);

    // Choose field
    cout << "Choose field to update: " << endl;
    cout << "1. Tournament name" << endl;
    cout << "2. Tournament date and time" << endl;
    cout << "3. Tournament entry fee" << endl;
    cout << "4. Maximum number of players" << endl;
    cout << "Enter Choice: ";
    int field = getValidatedChoice(1, 4);

    string update_query;
    string column_name;
    
    // Determine which column to update
    switch (field)
    {
        case 1: column_name = "tour_name"; break;
        case 2: column_name = "tour_datetime"; break;
        case 3: column_name = "tour_fee"; break;
        case 4: column_name = "max_players"; break;
        default:
            cout << "Invalid choice." << endl;
            return;
    }
    
    update_query = "UPDATE product SET " + column_name + " = ? WHERE tour_id = ?;";
    result_code = sqlite3_prepare_v2(db, update_query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Bind values based on field type
    switch (field)
    {
        case 1: // tournament name
        {
            string tournament_name;
            cout << "Enter new tournament name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, tournament_name);
            sqlite3_bind_text(stmt, 1, tournament_name.c_str(), -1, SQLITE_TRANSIENT);
            break;
        }
        case 2: // tournament date and time
        {
            cout << "Enter new tournament date and time: ";
            string date_time = getDateTimeFromUser();
            sqlite3_bind_text(stmt, 1, date_time.c_str(), -1, SQLITE_TRANSIENT);
            break;
        }
        case 3: // tournament entry fee
        {
            double entry_fee;
            cout << "Enter new entry fee: ";
            cin >> entry_fee;
            sqlite3_bind_double(stmt, 1, entry_fee);
            break;
        }
        case 4: // Maximum number of players
        {
            cout << "Enter maximum number of players (max player is 16): ";
            int max_players = getValidatedChoice(1, 16);
            sqlite3_bind_int(stmt, 1, max_players);
            break;
        }
        default:
            cout << "Invalid choice." << endl;
            sqlite3_finalize(stmt);
            return;
    }
    
    // the tour id might be 1-5 based on the printPage function but the actual tour_id should be in the database 
    sqlite3_bind_int(stmt, 2, tour_id);
    
    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Record updated successfully." << endl;
    }
    
    sqlite3_finalize(stmt);
}

void updateSaleItem(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    
    // Show sale items with readable info
    string query = "SELECT si.sale_item_id, s.sale_id, p.p_name, si.quantity, si.item_price "
                   "FROM sale_item si "
                   "JOIN product p ON si.p_code = p.p_code "
                   "JOIN sale s ON si.sale_id = s.sale_id;";
    
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    cout << "Choose the Sale Item to update: " << endl;
    printPage(stmt, 5, 0);
    int sale_item_id = getValidatedChoice(1, 5);
    sqlite3_finalize(stmt);

    // Get current product code and price
    query = "SELECT p_code, (SELECT p_price FROM product WHERE p_code = sale_item.p_code) as price "
            "FROM sale_item WHERE sale_item_id = ?;";
    result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error getting item details: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, sale_item_id);
    
    int p_code;
    double price;
    int sale_id;
    
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        p_code = sqlite3_column_int(stmt, 0);
        price = sqlite3_column_double(stmt, 1);
    }
    else
    {
        cout << "Sale item not found!" << endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);

    // Get new quantity
    cout << "Enter new quantity: ";
    int new_quantity = getValidatedChoice();
    
    // Calculate new item price
    double new_item_price = price * new_quantity;

    query = "UPDATE sale_item SET quantity = ?, item_price = ? WHERE sale_item_id = ?;";
    result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, new_quantity);
    sqlite3_bind_double(stmt, 2, new_item_price);
    sqlite3_bind_int(stmt, 3, sale_item_id);
    
    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Record updated successfully." << endl;
        
        // Update total_amount in sale table
        sqlite3_finalize(stmt);
        query = "UPDATE sale SET total_amount = "
                "(SELECT SUM(item_price) FROM sale_item WHERE sale_id = "
                "(SELECT sale_id FROM sale_item WHERE sale_item_id = ?)) "
                "WHERE sale_id = (SELECT sale_id FROM sale_item WHERE sale_item_id = ?);";
        
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK)
        {
            sqlite3_bind_int(stmt, 1, sale_item_id);
            sqlite3_bind_int(stmt, 2, sale_item_id);
            sqlite3_step(stmt);
        }
    }
    
    sqlite3_finalize(stmt);
}

void updateTournamentRegistration(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    
    // Show registrations with details
    string query = "SELECT tr.reg_id, t.tour_name, c.cus_fname || ' ' || c.cus_lname as customer, "
                   "ps.status_name, tr.registration_datetime "
                   "FROM tournament_registration tr "
                   "JOIN tournament t ON tr.tour_id = t.tour_id "
                   "JOIN customer c ON tr.cus_id = c.cus_id "
                   "JOIN payment_status ps ON tr.payment_status_id = ps.status_id;";
    
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting registrations: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    cout << "Choose Registration to Update: " << endl;
    printPage(stmt, 5, 0);
    int reg_id = getValidatedChoice(1, 10);
    sqlite3_finalize(stmt);
    
    // Choose new payment status
    query = "SELECT status_id, status_name FROM payment_status;";
    result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting payment status: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    cout << "Choose New Payment Status: " << endl;
    printPage(stmt, 5, 0);
    int new_status = getValidatedChoice(1, 5);
    sqlite3_finalize(stmt);
    
    // Update registration
    query = "UPDATE tournament_registration SET payment_status_id = ? WHERE reg_id = ?;";
    result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, new_status);
    sqlite3_bind_int(stmt, 2, reg_id);
    
    result_code = sqlite3_step(stmt);
    if (result_code != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Registration updated successfully!" << endl;
    }
    
    sqlite3_finalize(stmt);
}

// delete record
void deleteProduct(sqlite3 *db)
{
    string selectQuery = "SELECT p_code, p_name, p_price FROM product;";
    string deleteQuery = "DELETE FROM product WHERE p_code = ?;";
    deleteHelper(db, selectQuery, deleteQuery, "product");
}

void deleteCustomer(sqlite3 *db)
{
    string selectQuery = "SELECT cus_id, cus_fname, cus_lname, cus_email FROM customer;";
    string deleteQuery = "DELETE FROM customer WHERE cus_id = ?;";
    deleteHelper(db, selectQuery, deleteQuery, "customer");
}

void deleteSale(sqlite3 *db)
{
    string selectQuery = R"(
        SELECT sale_id, cus_fname || ' ' || cus_lname AS customer, sale_datetime, total_amount
        FROM sale
        JOIN customer ON sale.cus_id = customer.cus_id;
    )";
    string deleteQuery = "DELETE FROM sale WHERE sale_id = ?;";
    deleteHelper(db, selectQuery, deleteQuery, "sale");
}

void deleteTournament(sqlite3 *db)
{
    string selectQuery = "SELECT tour_id, tour_name FROM tournament;";
    string deleteQuery = "DELETE FROM tournament WHERE tour_id = ?;";
    deleteHelper(db, selectQuery, deleteQuery, "tournament");
}

void deleteSaleItem(sqlite3 *db)
{
    string selectQuery = R"(
        SELECT si.item_id, s.sale_id, p.p_name, si.quantity, si.subtotal
        FROM sale_item si
        JOIN sale s ON si.sale_id = s.sale_id
        JOIN product p ON si.p_code = p.p_code;
    )";
    string deleteQuery = "DELETE FROM sale_item WHERE item_id = ?;";
    deleteHelper(db, selectQuery, deleteQuery, "sale item");
}

void deleteTournamentRegistration(sqlite3 *db)
{
    string selectQuery = R"(
        SELECT tr.reg_id, t.tour_name, c.cus_fname || ' ' || c.cus_lname AS customer, ps.status_name
        FROM tournament_registration tr
        JOIN tournament t ON tr.tour_id = t.tour_id
        JOIN customer c ON tr.cus_id = c.cus_id
        JOIN payment_status ps ON tr.payment_status_id = ps.status_id;
    )";
    string deleteQuery = "DELETE FROM tournament_registration WHERE reg_id = ?;";
    deleteHelper(db, selectQuery, deleteQuery, "tournament registration");
}

// view sale
void viewSale(sqlite3 *db)
{

}

// view customer details
void viewCustomer(sqlite3 *db)
{

}

// view product details
void viewProduct(sqlite3 *db)
{

}

// helper functions
// print pages
void printPage(sqlite3_stmt *res, int rowsPerPage, int startNum)
{
    int stop;
    int i = 0;
    int numCols = sqlite3_column_count(res);

    while (i < rowsPerPage)
    {
        stop = sqlite3_step(res);
        if (stop != SQLITE_ROW)
            break;

        cout << startNum + i + 1 << ". ";

        for (int col = 0; col < numCols; ++col)
        {
            if (sqlite3_column_type(res, col) != SQLITE_NULL)
            {
                cout << sqlite3_column_text(res, col);
                if (col < numCols - 1)
                    cout << " ";
            }
        }
        cout << endl;
        i++;
    }
}

// Validates input
int getValidatedChoice()
{
    int choice;
    while (true)
    {
        cin >> choice;
        
        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number: ";
        }
        else
        {
            return choice;  
        }
    }
}


int getValidatedChoice(int minVal, int maxVal, int terminalVal)
{
    int choice;
    
    while (true)
    {
        cin >> choice;
        
        if (!cin)  // Non-integer input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "That is not a valid choice! Try again: ";
        }
        else if (choice == terminalVal)  
        {
            return choice;
        }
        else if (choice < minVal || choice > maxVal)
        {
            cout << "Choice must be between " << minVal << " and " << maxVal << ". Try again: ";
        }
        else  
        {
            return choice;
        }
    }
}

string getDateTimeFromUser()
{
    string date, time;
    regex date_pattern(R"(\d{4}-\d{2}-\d{2})");
    regex time_pattern(R"(\d{2}:\d{2}:\d{2})");
    
    while (true)
    {
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;
        
        if (!regex_match(date, date_pattern))
        {
            cout << "Invalid date format! Use YYYY-MM-DD" << endl;
            continue;
        }
        
        cout << "Enter time (HH:MM:SS): ";
        cin >> time;
        
        if (!regex_match(time, time_pattern))
        {
            cout << "Invalid time format! Use HH:MM:SS" << endl;
            continue;
        }
        
        return date + " " + time;
    }
}

bool deleteHelper(sqlite3 *db, const string &selectQuery, const string &deleteQuery,
                  const string &recordName, int minID = 1, int maxID = 9999)
{
    sqlite3_stmt *stmt;
    int result_code = sqlite3_prepare_v2(db, selectQuery.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing SELECT statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    cout << "\nChoose " << recordName << " to delete:\n";
    printPage(stmt, 5, 0);
    int id = getValidatedChoice(minID, maxID);
    sqlite3_finalize(stmt);

    cout << "Are you sure you want to delete this " << recordName << "? (1=Yes, 0=No): ";
    int confirm = getValidatedChoice(0, 1);
    if (confirm != 1)
    {
        cout << "Deletion cancelled.\n";
        return false;
    }

    result_code = sqlite3_prepare_v2(db, deleteQuery.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing DELETE statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);
    result_code = sqlite3_step(stmt);

    if (result_code != SQLITE_DONE)
    {
        cout << "Error deleting record: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    cout << recordName << " deleted successfully!\n";
    return true;
}
