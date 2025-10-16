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

void updateRecord(sqlite3 *);

void updateProduct(sqlite3 *);
void updateSale(sqlite3 *);
void updateCustomer(sqlite3 *);
void updateTournament(sqlite3 *);
void updateSaleItem(sqlite3 *);
void updateTournamentRegistration(sqlite3 *);


void deleteRecord(sqlite3 *);

void printPage(sqlite3_stmt *, int, int);

void addRecord(sqlite3 *);
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
                    &prompt, int page_size = 5);


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
            //addRecord(mydb);
            break;
        case 2:
            updateRecord(mydb);
            break;
        case 3:
            //deleteRecord(mydb);
            break;
        case 4:
            //viewSale(mydb);
            break;
        case 5 :
            //viewCustomer(mydb);
            break;
        case 6 :
            //viewProduct(mydb);
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
            //updateProduct(db);
            break;
        case 2:
            //updateSale(db);
            break;
        case 3:
            //updateCustomer(db);
            break;
        case 4:
            //updateTournament(db);
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

void printPages(sqlite3_stmt *stmt, int rowPerPage) {
    int total = 0, page = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) total++;
    sqlite3_reset(stmt);
    int pages = (total + rowPerPage - 1) / rowPerPage;
    char ch;

    do {
        sqlite3_reset(stmt);
        for (int i = 0; i < page * rowPerPage; i++) sqlite3_step(stmt);

        cout << "\n-- Page " << page + 1 << "/" << pages << " --\n";
        for (int r = 0; r < rowPerPage && sqlite3_step(stmt) == SQLITE_ROW; r++) {
            cout << (page * rowPerPage + r + 1) << ". ";
            for (int c = 0; c < sqlite3_column_count(stmt); c++) {
                cout << sqlite3_column_text(stmt, c);
                if (c < sqlite3_column_count(stmt) - 1) cout << " - ";
            }
            cout << "\n";
        }

        cout << "(n) Next (p) Prev (q) Quit: ";
        cin >> ch;
        if (ch == 'n' && page < pages - 1) page++;
        else if (ch == 'p' && page > 0) page--;
    } while (ch != 'q');
}

// update record



void updateSaleItem(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    
    // Show sale items with readable info
    string query = "SELECT si.sale_item_id, s.sale_id, p.p_name, si.quantity, si.item_price "
                   "FROM sale_item si "
                   "JOIN product p ON si.p_code = p.p_code "
                   "JOIN sale s ON si.sale_id = s.sale_id;";
    
    if(!prepareStatement(db, query, &stmt)){
        cout << "Error selecting record: " << sqlite3_errmsg(db);
        return;
    }
    
    cout << "Choose the Sale Item to update: " << endl;
    printPage(stmt, 5, 0);
    sqlite3_reset(stmt);

    int sale_item_id = getID(stmt, getValidatedChoice(1, 5)-1);
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
    
    cout << "Choose Registration to Update: " << endl;
    printPage(stmt, 5, 0);
    sqlite3_reset(stmt);

    int reg_id = getID(stmt, getValidatedChoice(1, 5)-1);
    sqlite3_finalize(stmt);
    
    // Choose new payment status
    query = "SELECT payment_status_id, status_name FROM payment_status;";
    if(!prepareStatement(db, query, &stmt))
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

    // confirm deletion
    cout << "Are you sure you want to delete this " << recordName << "? (1=Yes, 0=No): ";
    int confirm = getValidatedChoice(0, 1);
    if (confirm != 1)
    {
        cout << "Deletion cancelled.\n";
        return false;
    }

    // prepare statement for delete duery
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
    printPage(stmt, page_size, 0);
    sqlite3_reset(stmt);
    
    int choice = getValidatedChoice(1, page_size);
    int selected_id = getID(stmt, choice - 1);
    sqlite3_finalize(stmt);
    
    return selected_id;
}