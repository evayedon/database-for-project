#include <iostream>
#include <string>
#include <sqlite3.h>
#include <limits>
#include <iomanip>

using namespace std;

void printMainMenu();
int mainMenu();
void addRecord(sqlite3 *);
void addCustomer(sqlite3 *);
// sub-menu for addRecord
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
void printPage(sqlite3_stmt *res, int rowsPerPage, int startNum);

// Get and validate user choice
int getValidatedChoice(int minValue, int maxValue, int terminalValue = -1)
{
    int choice;
    cin >> choice;

    while ((!cin || choice < minValue || choice > maxValue) && terminalValue)
    {
        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            cout << "That is not a valid choice! Try again!" << endl;
            cin >> choice;
            continue;
        }

        if (choice == terminalValue)
            break;

        if (choice < minValue || choice > maxValue)
        {
            cout << "Choice must be between " << minValue << " and " << maxValue << ". Try again: ";
            cin >> choice;
            continue;
        }
    }
    return choice;
}

int main()
{
    int choice;

    sqlite3 *mydb;

    int rc = sqlite3_open_v2("gameZone.db", &mydb, SQLITE_OPEN_READWRITE, NULL);

    cout << "Welcome to GameZone" << endl;
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
        return 0;
    default:
        cout << "That is not a valid choice." << endl;
    }
}

// print main meu
void printMainMenu()
{
    cout << "Please choose an option (enter -1 to quit):  " << endl;
    cout << "1. Add Record" << endl;
    cout << "2. Update Record" << endl;
    cout << "3. Delete Record" << endl;
    cout << "Enter Choice: " << endl;
}

// main menu
int mainMenu()
{
    printMainMenu();
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
    cout << "Select table to add record to (or type -1 to go back):" << endl;
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
        mainMenu();
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
    cout << "Select table to add record to (or type -1 to go back):" << endl;
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
        mainMenu();
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
    cout << "Select table to add record to (or type -1 to go back):" << endl;
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
        mainMenu();
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
    sqlite3_stmt *stmt;
    // choose customer
    query = "select cus_id, cus_fname, cus_lname from customer;";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return;
    }
    else
    {
        cout << "Choose the Customer for the Sale: " << endl;
        printPage(stmt, 5, 0);
        cus_id = getValidatedChoice(1, 5); // need to change 5 to number of records in customer table
        sqlite3_finalize(stmt);
    }

    string query1 = "insert into sale (sale_datetime, cus_id, total_amount, discount_applied) values (datetime('now'), ?, (select sum(item_price) from sale_item where sale_item.sale = sale.sale_id));";

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
        cout << "Error inserting record: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
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
    }
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
    }
    else
    {
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
    }
    sqlite3_finalize(stmt);
}

void addSaleItem(sqlite3 *db)
{
    string query;
    int sale_id;
    int p_id;
    int quantity;
    sqlite3_stmt *stmt;
    // choose sale
    query = "select sale_id, cus_fname, cus_lname, sale_datetime from sale join customer on sale.cus_id = customer.cus_id;";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return;
    }
    else
    {
        cout << "Choose the Sale to add item: " << endl;
        printPage(stmt, 5, 0);
        sale_id = getValidatedChoice(1, 5); // need to change 5 to number of records in sale table
        sqlite3_finalize(stmt);
    }
    // choose product
    query = "select p_code, p_name, p_price from product;";
    result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return;
    }
    else
    {
        cout << "Choose the Product to add: " << endl;
        printPage(stmt, 5, 0);
        p_id = getValidatedChoice(1, 5); // need to change 5 to number of records in product table

        cout << "Enter quantity: ";
        cin >> quantity;
        string query1 = "insert into sale_item (sale_id, p_code, quantity, item_price) values (?, ?, ?, ?);";
        result_code = sqlite3_prepare_v2(db, query1.c_str(), -1, &stmt, NULL);
        if (result_code != SQLITE_OK)
        {
            cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
            return;
        }
        sqlite3_bind_int(stmt, 1, sale_id);
        sqlite3_bind_int(stmt, 2, p_id);
        sqlite3_bind_int(stmt, 3, quantity);
        sqlite3_bind_double(stmt, 4, quantity *  (sqlite3_column_double(stmt, 2)));        
        result_code = sqlite3_step(stmt);
        if (result_code != SQLITE_DONE)
        {
            cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        }
        else
        {
            cout << "Record inserted successfully." << endl;
        }
    }
    sqlite3_finalize(stmt);
}

void addTournamentRegistration(sqlite3 *db)
{
    int tour_id;
    int cus_id;
    sqlite3_stmt *stmt;
    int status_id;
    // choose tournament
    string query = "select tour_id, tour_name from tournament;";
    int result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return;
    }
    else
    {

        cout << "Choose the Tournament to register: " << endl;
        printPage(stmt, 5, 0);
        tour_id = getValidatedChoice(1, 5); 
        sqlite3_finalize(stmt);
    }
    // choose customer
    query = "select cus_id, cus_fname, cus_lname from customer;";
    result_code = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error selecting records: " << sqlite3_errmsg(db) << endl;
        return; 
    }
    else
    {
        cout  << "Choose the Customer to register: " << endl;
        printPage(stmt, 5, 0);
        cus_id = getValidatedChoice(1, 5);
        sqlite3_finalize(stmt);
    }
    // get payment status
    cout << "Enter payment status: ";
    cout << "1. Pending" << endl;
    cout << "2. Paid" << endl;
    cout << "3. Waived" << endl;
    status_id = getValidatedChoice(1, 3);

    string query1 = "insert into tournament_registration (tour_id, cus_id, registration_datetime, payment_status) "
                    "values (?, ?, datetime('now'), (select status_name from payment_status where status_id = ?));";

    result_code = sqlite3_prepare_v2(db, query1.c_str(), -1, &stmt, NULL);
    if (result_code != SQLITE_OK)
    {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, tour_id);
    sqlite3_bind_int(stmt, 2, cus_id);
    sqlite3_bind_int(stmt, 3, status_id);

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
}
void updateSale(sqlite3 *db)
{
}
void updateCustomer(sqlite3 *db)
{
}
void updateTournament(sqlite3 *db)
{
}
void updateSaleItem(sqlite3 *db)
{
}
void updateTournamentRegistration(sqlite3 *db)
{
}

// delete record
void deleteProduct(sqlite3 *db)
{
}
void deleteSale(sqlite3 *db)
{
}
void deleteCustomer(sqlite3 *db)
{
}
void deleteTournament(sqlite3 *db)
{
}
void deleteSaleItem(sqlite3 *db)
{
}
void deleteTournamentRegistration(sqlite3 *db)
{
}

// view sale
void viewSale(sqlite3 *)
{

}

// view customer details
void viewCustomer(sqlite3 *)
{

}

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
                    cout << " | ";
            }
        }
        cout << endl;
        i++;
    }
}


