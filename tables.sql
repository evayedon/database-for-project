--CUSTOMER table
CREATE TABLE customer (
    cus_id INTEGER NOT NULL PRIMARY KEY,
    cus_fname TEXT NOT NULL, 
    cus_lname TEXT NOT NULL,
    cus_phone TEXT NOT NULL,
    cus_email TEXT NOT NULL UNIQUE,
    membership_id INTEGER DEFAULT (1) REFERENCES membership(membership_id)
);

--PRODUCT table
CREATE TABLE product (
    p_code INTEGER NOT NULL PRIMARY KEY,
    p_name TEXT NOT NULL UNIQUE,
    category_id INTEGER NOT NULL REFERENCES category(category_id),
    p_price REAL NOT NULL CHECK (p_price > 0),
    p_quantity INTEGER NOT NULL CHECK (p_quantity >= 0),
    min_stock_level INTEGER NOT NULL CHECK (min_stock_level >= 0)
) STRICT;

--SALE table
-- improvement: multiple sales per customer so p_code, quanity should be removed from sale table and added to sale_item table
-- added payment_status
CREATE TABLE sale (
    sale_id INTEGER NOT NULL PRIMARY KEY, 
    sale_datetime TEXT DEFAULT CURRENT_TIMESTAMP NOT NULL,  
    cus_id INTEGER NOT NULL REFERENCES customer(cus_id), 
    total_amount REAL NOT NULL CHECK (total_amount >= 0), 
    discount_applied REAL DEFAULT 0 NOT NULL CHECK (discount_applied >= 0 AND discount_applied <= 100),   
    payment_status_id INTEGER DEFAULT 3 NOT NULL REFERENCES payment_status(payment_status_id)
)STRICT;

--TOURNAMENT table
CREATE TABLE tournament (
    tour_id INTEGER NOT NULL PRIMARY KEY, 
    tour_name TEXT NOT NULL, 
    tour_datetime TEXT NOT NULL,
    tour_fee REAL NOT NULL, 
    max_players INTEGER DEFAULT 16 NOT NULL CHECK (max_players > 0 AND max_players <= 16)
);

--TOURNAMENT_REGISTRATION table
CREATE TABLE tournament_registration (
    reg_id INTEGER NOT NULL PRIMARY KEY, 
    tour_id INTEGER NOT NULL REFERENCES tournament(tour_id), 
    cus_id INTEGER NOT NULL REFERENCES customer(cus_id), 
    registration_datetime TEXT DEFAULT CURRENT_TIMESTAMP NOT NULL, 
    payment_status_id INTEGER NOT NULL REFERENCES payment_status(payment_status_id), 
    --UNIQUE CONSTRAINT
    UNIQUE(tour_id, cus_id)
) STRICT;

--SALE_ITEM table
CREATE TABLE sale_item (
    sale_item_id INTEGER NOT NULL PRIMARY KEY,
    sale_id INTEGER NOT NULL REFERENCES sale(sale_id),
    p_code INTEGER NOT NULL REFERENCES product(p_code),
    quantity INTEGER NOT NULL CHECK (quantity > 0),
    item_price REAL NOT NULL CHECK (item_price > 0)
) STRICT;

--category
CREATE TABLE category (
    category_id INTEGER NOT NULL PRIMARY KEY,
    category_name TEXT NOT NULL UNIQUE
) STRICT;

-- membership
CREATE TABLE membership (
    membership_id INTEGER NOT NULL PRIMARY KEY,
    membership_status TEXT NOT NULL UNIQUE,
    discount_rate INTEGER NOT NULL CHECK (discount_rate >= 0 AND discount_rate <= 100)
) STRICT;

-- added payment status
CREATE TABLE payment_status (
    payment_status_id INTEGER NOT NULL PRIMARY KEY,
    status_name TEXT NOT NULL UNIQUE
) STRICT;

