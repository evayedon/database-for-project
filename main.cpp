#include <iostream>
#include <string>
#include <sqlite3.h>
#include <limits>
#include <iomanip>
#include <regex>

using namespace std;

// ==========MAIN FUNCTIONS ===========

// menu function
void printMainMenu();
int mainMenu();

void addRecord(sqlite3 *);
// sub-menus for addRecord
void addCustomer(sqlite3 *);
void addProduct(sqlite3 *);
void addSale(sqlite3 *);
void addCustomer(sqlite3 *);
void addTournament(sqlite3 *);
void addSaleItem(sqlite3 *);
void addTournamentRegistration(sqlite3 *);

void updateRecord(sqlite3 *);
// sub-menus for update record
void updateProduct(sqlite3 *);
void updateSale(sqlite3 *);
void updateCustomer(sqlite3 *);
void updateTournament(sqlite3 *);
void updateSaleItem(sqlite3 *);
void updateTournamentRegistration(sqlite3 *);

void deleteRecord(sqlite3 *);
// sub-menus for delete record
void deleteProduct(sqlite3 *);
void deleteSale(sqlite3 *);
void deleteCustomer(sqlite3 *);
void deleteTournament(sqlite3 *);
void deleteSaleItem(sqlite3 *);
void deleteTournamentRegistration(sqlite3 *);

// view records
void viewSale(sqlite3 *);
void viewCustomer(sqlite3 *);
void viewProduct(sqlite3 *);
void printPages(sqlite3_stmt *, int = 10);

// ========== HELPER FUNCTIONS =========
int getValidatedChoice();
int getValidatedChoice(int, int, int = -1);
string getDateTimeFromUser();
void startPage(sqlite3 *);
bool deleteHelper(sqlite3 *, const string &, const string &,
                  const string &, int = 1, int = 9999);
int getID(sqlite3_stmt *, int);
bool prepareStatement(sqlite3 *db, const string &query, sqlite3_stmt **stmt);
bool executeStatement(sqlite3_stmt *stmt);
double getValidatedPrice();
int selectFromList(sqlite3 *db, const string &query, const string 
                    &prompt, int page_size = 10);


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
        case 4:
            viewSale(mydb);
            break;
        case 5 :
            viewCustomer(mydb);
            break;
        case 6 :
            viewProduct(mydb);
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
    cout << "4. View Sale Records" << endl;
    cout << "5. View Customer Records" << endl;
    cout << "6. View Product Records" << endl;
}

// main menu
int mainMenu()
{

    printMainMenu();
    cout << "Enter Choice: ";
    int choice = getValidatedChoice(1, 6);
    return choice;
}


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


// add record
void addProduct(sqlite3 *db)
{
    string p_name;
    double p_price;
    int p_quantity, min_stock_level;
    sqlite3_stmt *stmt;
    // get product information
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
    p_price = getValidatedPrice();
    cout << "Enter product quantity: ";
    p_quantity  = getValidatedChoice();
    cout << "Enter minimum stock level: ";
    min_stock_level  = getValidatedChoice();

    string query = "INSERT INTO Product (p_name, category_id, p_price, p_quantity, min_stock_level) "
                   "VALUES (?,?,?,?,?);";
    
    if (!prepareStatement(db, query, &stmt))
        return;
    
    sqlite3_bind_text(stmt, 1, p_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, category_id);
    sqlite3_bind_double(stmt, 3, p_price);
    sqlite3_bind_int(stmt, 4, p_quantity);
    sqlite3_bind_int(stmt, 5, min_stock_level);

    if (executeStatement(stmt))
        cout << "Product added successfully." << endl;
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
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }

    // Payment status
    cout << "Enter payment status:\n";
    cout << "1. Pending\n2. Paid\n3. Unpaid\n4. Cancel\n";
    int payment_status_id = getValidatedChoice(1, 4);

    // Insert sale - 3 placeholders for 3 values (sale_datetime is generated)
    string query1 = "INSERT INTO sale (sale_datetime, cus_id, total_amount, discount_applied, payment_status_id) "
                    "VALUES (datetime('now'), ?, ?, ?,?);";

    if (!prepareStatement(db, query1, &stmt))
        return;

    sqlite3_bind_int(stmt, 1, cus_id);
    sqlite3_bind_double(stmt, 2, 0.0);
    sqlite3_bind_double(stmt, 3, discount);
    sqlite3_bind_int(stmt, 4, payment_status_id);

    if (executeStatement(stmt))
        cout << "Sale created successfully." << endl;
  
    sqlite3_finalize(stmt);  
}

void addCustomer(sqlite3 *db)
{
    string c_fname, c_lname, c_email, c_phone;
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

    if (!prepareStatement(db, query, &stmt))
        return;

    sqlite3_bind_text(stmt, 1, c_fname.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, c_lname.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, c_phone.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, c_email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, membership_status);
    
    if (executeStatement(stmt))
        cout << "Customer added successfully." << endl;
    sqlite3_finalize(stmt);
}

void addTournament(sqlite3 *db)
{
    string t_name, t_date;
    double t_entry_fee;
    int max_players;
    sqlite3_stmt *stmt;

    // Get tournament information
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
    
    if (!prepareStatement(db, query, &stmt))
        return;

    sqlite3_bind_text(stmt, 1, t_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, t_date.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, t_entry_fee);
    sqlite3_bind_int(stmt, 4, max_players);

    if (executeStatement(stmt))
        cout << "Tournament created successfully." << endl;
 
    sqlite3_finalize(stmt);
}

void addSaleItem(sqlite3 *db)
{
    int p_code, quantity, available_stock;
    double p_price;
    sqlite3_stmt *stmt;
    
    // Begin transaction
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

    // Choose sale
    string query = "SELECT sale_id, cus_fname, cus_lname, sale_datetime "
            "FROM sale JOIN customer ON sale.cus_id = customer.cus_id;";
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    
    // get sale
    string prompt = "Choose the Sale to add item: " ;
    int sale_id = selectFromList(db, query, prompt);
    sqlite3_finalize(stmt);
    
    
    // Choose product
    query = "SELECT p_code, p_name, p_price FROM product;";
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }

    // add products
    prompt = "Choose the Product to add: ";
    p_code = selectFromList(db, query, prompt);
    sqlite3_finalize(stmt);
    
    // Select product  
    query = "SELECT p_code, p_name, p_price FROM product;";
    p_code = selectFromList(db, query, "Choose the Product to add:");
    if (p_code == -1)
    {
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return;
    }
    
    // Get product details using helper functions
    // product price
    query = "SELECT p_price FROM product WHERE p_code = ?;";
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error: Product not found!" << endl;
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        p_price = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
    }

    // procuct quantity to get available stock
    query = "SELECT p_quantity FROM product WHERE p_code = ?;";
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error: Could not get stock level!" << endl;
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return;
    }
    
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        available_stock = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
    }

    // Validate quantity
    cout << "Available stock: " << available_stock << endl;
    cout << "Enter quantity: ";
    quantity = getValidatedChoice(1, available_stock);
    
    double item_price = quantity * p_price;
    
    // Insert sale item
    query = "INSERT INTO sale_item (sale_id, p_code, quantity, item_price) VALUES (?, ?, ?, ?);";
    if (!prepareStatement(db, query, &stmt))
    {
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return;
    }
    
    sqlite3_bind_int(stmt, 1, sale_id);
    sqlite3_bind_int(stmt, 2, p_code);
    sqlite3_bind_int(stmt, 3, quantity);
    sqlite3_bind_double(stmt, 4, item_price);
    
    if (!executeStatement(stmt))
    {
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return;
    }

    // Update inventory
    query = "UPDATE product SET quantity = quantity - ? WHERE p_code = ?";
    if (!prepareStatement(db, query, &stmt))
    {
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return;
    }
    
    sqlite3_bind_int(stmt, 1, quantity);
    sqlite3_bind_int(stmt, 2, p_code);

    if (!executeStatement(stmt))
    {
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return;
    }
    sqlite3_finalize(stmt);
        
    // Update the total_amount in the sale table
    query = "UPDATE sale SET total_amount = "
            "(SELECT SUM(item_price) FROM sale_item WHERE sale_id = ?) "
            "WHERE sale_id = ?;";
    if (!prepareStatement(db, query, &stmt))
    {
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return;
    }
    
    sqlite3_bind_int(stmt, 1, sale_id);
    sqlite3_bind_int(stmt, 2, sale_id);
    
    if (!executeStatement(stmt))
    {
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return;
    }

    sqlite3_finalize(stmt);

    // Commit transaction
    if (sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL) == SQLITE_OK)
    {
        cout << "Sale item added successfully. Inventory updated." << endl;
    }
    else
    {
        cout << "Error committing transaction!" << endl;
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
    }
}

void addTournamentRegistration(sqlite3 *db)
{
    int tour_id;
    int cus_id;
    sqlite3_stmt *stmt;
    string prompt;

    // Choose tournament
    string query = "SELECT tour_id, tour_name FROM tournament;";
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting tournaments: " << sqlite3_errmsg(db) << endl;
        return;
    }

    prompt = "Choose the Tournament to register: ";
    tour_id  = selectFromList(db, query, prompt);
    sqlite3_finalize(stmt);

    // Choose customer
    query = "SELECT cus_id, cus_fname, cus_lname FROM customer;";
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting customers: " << sqlite3_errmsg(db) << endl;
        return;
    }

    prompt = "Choose the Customer to register:";
    cus_id = selectFromList(db, query, prompt);
    sqlite3_finalize(stmt);

    // Payment status
    cout << "Enter payment status:\n";
    cout << "1. Pending\n2. Paid\n3. Unpaid\n4. Cancel\n";
    int payment_status_id = getValidatedChoice(1, 4);

    query = "INSERT INTO tournament_registration "
                    "(tour_id, cus_id, registration_datetime, payment_status_id) "
                    "VALUES (?, ?, datetime('now'), ?);";
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, tour_id);
    sqlite3_bind_int(stmt, 2, cus_id);
    sqlite3_bind_int(stmt, 3, payment_status_id);
 
    if (!executeStatement(stmt))
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
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // need to change for more than 5 products
    string prompt = "Choose the product to update: " ;
    // printPages(stmt);
    // sqlite3_reset(stmt);

    int p_code = selectFromList(db, query, prompt);
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

    string update_query, column_name;
    
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
    
    query = "UPDATE product SET " + column_name + " = ? WHERE p_code = ?;";
    if (!prepareStatement(db, query, &stmt))
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
            price = getValidatedPrice();
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
    
    if (!executeStatement(stmt))
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
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string prompt = "Choose the sale to update:c   ";
    // printPages(stmt);
    // sqlite3_reset(stmt);

    int sale_id = selectFromList(db, query, prompt);
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
    
    query = "UPDATE sale SET " + column_name + " = ? WHERE sale_id = ?;";
    if (!prepareStatement(db, query, &stmt))
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
    
    if (!executeStatement(stmt))
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
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    string prompt = "Choose the Customer to update: ";
    // printPages(stmt);
    // sqlite3_reset(stmt);

    int cus_id = selectFromList(db, query, prompt);
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
    query = "UPDATE customer SET " + column_name + " = ? WHERE cus_id = ?;";
    if (!prepareStatement(db, query, &stmt))
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
    if (executeStatement(stmt))
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
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }

    string prompt = "Choose the tournament to update: ";
    // printPages(stmt);
    // sqlite3_reset(stmt);

    int tour_id = selectFromList(db, query, prompt);

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
    
    query = "UPDATE product SET " + column_name + " = ? WHERE tour_id = ?;";
    if (!prepareStatement(db, query, &stmt))
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
            cout << "Enter new entry fee: ";
            double entry_fee = getValidatedPrice();
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
    
    if(!executeStatement(stmt))
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
    else
        cout << "Record updated successfully." << endl;

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
    
    if(!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    
    string prompt = "Choose the Sale Item to update: \n";

    // come baack to  check it deduct getID(stmt, getValidatedChoice(1, 5)-1)
    int sale_item_id = selectFromList(db, query, prompt);
    sqlite3_finalize(stmt);

    // Get current product code and price
    query = "SELECT p_code, (SELECT p_price FROM product WHERE p_code = sale_item.p_code) as price "
            "FROM sale_item WHERE sale_item_id = ?;";
    if(!prepareStatement(db, query, &stmt))
    {
        cout << "Error getting item details: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, sale_item_id);
    
    int p_code;
    double price;
    
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
    if(prepareStatement(db, query, &stmt))
    
    sqlite3_bind_int(stmt, 1, new_quantity);
    sqlite3_bind_double(stmt, 2, new_item_price);
    sqlite3_bind_int(stmt, 3, sale_item_id);
    
    if(!executeStatement(stmt))
    {
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        sqlite3_finalize(stmt);
        return;
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
        
        if(prepareStatement(db, query, &stmt))
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
    
    if(!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting registrations: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    string prompt = "Choose Registration to Update: \n";

    int reg_id = selectFromList(db, query, prompt);
    sqlite3_finalize(stmt);
    
    // Choose new payment status
    query = "SELECT payment_status_id, status_name FROM payment_status;";
    if(!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting payment status: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    cout << "Choose New Payment Status: " << endl;
    printPages(stmt);
    int new_status = getValidatedChoice(1, 4);
    sqlite3_finalize(stmt);
    
    // Update registration
    query = "UPDATE tournament_registration SET payment_status_id = ? WHERE reg_id = ?;";
    if(!prepareStatement(db, query, &stmt))
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, new_status);
    sqlite3_bind_int(stmt, 2, reg_id);
    
    if(!executeStatement(stmt))
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
    string query = R"(SELECT s.sale_id, c.cus_fname || ' ' || c.cus_lname AS customer,
                        s.sale_datetime, s.total_amount, ps.payment_status_id
                     FROM sale s
                     JOIN customer c ON s.cus_id = c.cus_id
                     JOIN payment_status ps ON s.payment_status_id = ps.payment_status_id;)";
    sqlite3_stmt *stmt;
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting sales: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    string prompt = "Select Sale Record:\n";

    int sale_id = selectFromList(db, query, prompt);
    sqlite3_finalize(stmt);

    // Show sale items for the selected sale
    query = R"(SELECT si.sale_item_id, p.p_name, si.quantity, si.item_price
              FROM sale_item si
              JOIN product p ON si.p_code = p.p_code
              WHERE si.sale_id = ?;)";
    if (!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting sale items: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_bind_int(stmt, 1, sale_id);
    cout << "Sale Items for Sale ID " << sale_id << ":\n";
    printPages(stmt);
    sqlite3_finalize(stmt);
    cout << "End of sale items." << endl;
    cout << endl;
}

// view customer details
void viewCustomer(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    string query = R"(SELECT cus_id, cus_fname '| |' cus_lname, cus_phone, cus_email, membership_status "
                        FROM customer c JOIN membership m ON c.membership_id = m.membership_id;)";
    if(!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting customer items: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }

    string prompt = "Select Customer Record:\n"; 

    int cus_id = selectFromList(db, query, prompt);
    sqlite3_finalize(stmt);

    query = R"(SELECT cus_id, cus_fname, cus_lname, cus_phone, cus_email, membership_status "
                FROM customer c JOIN membership m ON c.membership_id = m.membership_id
                WHERE cus_id = ?;)";
    if(!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting Customer: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_bind_int(stmt, 1, cus_id);

    if (executeStatement(stmt))
    {

        string cus_fname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string cus_lname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string cus_email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string cus_phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        string membership_status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        sqlite3_finalize(stmt);
        cout << "Customer Information" << endl;
        cout << "Customer ID: " << cus_id << endl;;
        cout << "Name: " << cus_fname + " " + cus_lname << endl;
        cout << "Phone: " << cus_phone << endl;
        cout << "Membership status: " << membership_status << endl;

        cout << "End of customer info." << endl;
    }
    else
        cout << "Product not found" << endl;
    cout << endl;
}

// view product details
void viewProduct(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    string query = "SELECT p_code, p_name, c.category_name "
                    "FROM product p JOIN category c ON p.category_id = c.category_id;";
    if(!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting product items: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }

    string prompt = "Select Product Record:\n"; 

    int p_code = selectFromList(db, query, prompt);
    sqlite3_finalize(stmt);

    query = "SELECT p_code, p_name, c.category_name, p_price, p_quantity, min_stock_level "
                "FROM product p JOIN category c ON p.category_id = c.category_id "
                "WHERE p_code = ?;";
    if(!prepareStatement(db, query, &stmt))
    {
        cout << "Error selecting Customer: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_bind_int(stmt, 1, p_code);

    if(executeStatement(stmt))
    {
        string p_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        double price = (sqlite3_column_double(stmt, 3));
        int quantity = (sqlite3_column_int(stmt, 4));
        int min_stock_level = (sqlite3_column_int(stmt, 5));
        sqlite3_finalize(stmt);

        cout << "Product Information" << endl;
        cout << "Product ID: " << p_code << endl;;
        cout << "Name: " << p_name  << "        Category: " << category << "    Price: $" << price << endl;
        cout << "Quantity: " << quantity << "         Minimum stock level: " << min_stock_level << endl;
        cout << "End of product info." << endl;

    }
    else
        cout << "Product not found" << endl;
    cout << endl;
}


// === HELPER FUNCTIONS DEFINITION ===
// print pages

void printPages(sqlite3_stmt *stmt, int rowsPerPage) 
{
    int total = 0, page = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) total++;
    sqlite3_reset(stmt);
    int pages = (total + rowsPerPage - 1) / rowsPerPage;
    char ch;
    do {
        sqlite3_reset(stmt);
        for (int i = 0; i < page * rowsPerPage; i++) sqlite3_step(stmt);
        cout << "\n-- Page " << page + 1 << "/" << pages << " --\n";
        for (int r = 0; r < rowsPerPage && sqlite3_step(stmt) == SQLITE_ROW; r++) {
            cout << (page * rowsPerPage + r + 1) << ". ";
            for (int c = 0; c < sqlite3_column_count(stmt); c++) {
                cout << sqlite3_column_text(stmt, c);
                if (c < sqlite3_column_count(stmt) - 1) cout << " - ";
            }
            cout << "\n";
        }
        if (total > rowsPerPage) {
            cout << "(n) Next (p) Prev (q) Quit: ";
            cin >> ch;
            if (ch == 'n' && page < pages - 1) page++;
            else if (ch == 'p' && page > 0) page--;
        } else {
            ch = 'q';
        }
    } while (ch != 'q');
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

// Helper function for date collection in ISO84
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
                  const string &recordName, int minID, int maxID)
{
    sqlite3_stmt *stmt;

    // prepare statement for select query
    if(!prepareStatement(db, selectQuery, &stmt))
    {
        cout << "Error preparing SELECT statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    string prompt = "\nChoose " + recordName + " to delete:\n";
    int id = selectFromList(db, selectQuery, prompt);
    sqlite3_finalize(stmt);

    // confirm deletion
    cout << "Are you sure you want to delete this " << recordName << "? (1=Yes, 0=No): ";
    int confirm = getValidatedChoice(0, 1);
    if (confirm != 1)
    {
        cout << "Deletion cancelled.\n";
        return false;
    }

    // prepare statement for delete duery
    if(!prepareStatement(db, deleteQuery, &stmt))
    {
        cout << "Error preparing DELETE statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);
    if(!executeStatement(stmt))
    {
        cout << "Error deleting record: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    cout << recordName << " deleted successfully!\n";
    return true;
}

// get the ID
int getID(sqlite3_stmt *stmt, int row)
{
    int currentRow = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        if (currentRow == row)
        {
            return sqlite3_column_int(stmt, 0);
        }
        currentRow++;
    }
    return -1; // Not found
}

// Helper function to prepare a statement
bool prepareStatement(sqlite3 *db, const string &query, sqlite3_stmt **stmt)
{
    int result = sqlite3_prepare_v2(db, query.c_str(), -1, stmt, NULL);
    if (result != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    return true;
}

// Helper function to execute a prepared statement
bool executeStatement(sqlite3_stmt *stmt)
{
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        cout << "Error executing statement: " << sqlite3_errmsg(sqlite3_db_handle(stmt)) << endl;
        return false;
    }
    return true;
}

double getValidatedPrice()
{
    double value;
    while (true)
    {
        cin >> value;
        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input." << endl;
            continue;
            
        }
        else

            return value;
       
    }
}

// Helper function to display a list and get user selection
int selectFromList(sqlite3 *db, const string &query, const string &prompt, int page_size)
{
    sqlite3_stmt *stmt;
    if (!prepareStatement(db, query, &stmt))
        return -1;
    
    cout << prompt << endl;
    printPages(stmt, page_size);
    sqlite3_reset(stmt);
    
    int choice = getValidatedChoice(1, page_size);
    int selected_id = getID(stmt, choice - 1);
    sqlite3_finalize(stmt);
    
    return selected_id;
}