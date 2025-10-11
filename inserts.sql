-- GameZone Store Sample Data Insertion

-- Insert 5 CUSTOMER records
INSERT INTO customer (cus_id, cus_fname, cus_lname, cus_phone, cus_email, membership_id) VALUES
(1, 'Alex', 'Johnson', '555-0101', 'alex.johnson@email.com', 2),
(2, 'Maria', 'Rodriguez', '555-0102', 'maria.rodriguez@email.com', 3),
(3, 'David', 'Chen', '555-0103', 'david.chen@email.com', 2),
(4, 'Sarah', 'Williams', '555-0104', 'sarah.williams@email.com', 1),
(5, 'Mike', 'Thompson', '555-0105', 'mike.thompson@email.com', 2);

-- Insert 5 PRODUCT records
INSERT INTO product (p_code, p_name, category_id, p_price, p_quantity, min_stock_level) VALUES
(1001, 'FIFA 24', 1, 59.99, 25, 5),
(1002, 'PlayStation 5 Controller', 3, 69.99, 15, 3),
(1003, 'Nintendo Switch', 2, 299.99, 8, 2),
(1004, 'Call of Duty: Modern Warfare III', 1, 69.99, 30, 5),
(1005, 'Xbox Wireless Headset', 3, 99.99, 12, 3);

-- Insert 5 SALE records
-- improvement: multiple sales per customer and many products per sale so p_code, quanity have been removed from sale table and added to sale_item table
INSERT INTO sale (sale_id, sale_datetime, cus_id, total_amount, discount_applied) VALUES
(2001, '2024-01-15 14:30:00', 1, 59.99, 0),
(2002, '2024-01-16 10:15:00', 2, 299.99, 10),
(2003, '2024-01-16 16:45:00', 3, 69.99, 5),
(2004, '2024-01-17 11:20:00', 1, 69.99, 0),
(2005, '2024-01-17 15:10:00', 5, 99.99, 15);

-- Insert 5 TOURNAMENT records
INSERT INTO tournament (tour_id, tour_name, tour_datetime, tour_fee, max_players) VALUES
(3001, 'FIFA 24 Championship', '2024-02-15 19:00:00', 10.00, 16),
(3002, 'Retro Gaming Night', '2024-02-22 18:00:00', 0.00, 12),
(3003, 'Call of Duty Tournament', '2024-03-01 20:00:00', 15.00, 16),
(3004, 'Fighting Game Friday', '2024-02-09 19:30:00', 5.00, 8),
(3005, 'Super Smash Bros Ultimate', '2024-02-29 18:30:00', 12.00, 16);

-- Insert 5 TOURNAMENT_REGISTRATION records
INSERT INTO tournament_registration (reg_id, tour_id, cus_id, registration_datetime, payment_status) VALUES
(4001, 3001, 1, '2024-01-20 09:00:00', 'Paid'),
(4002, 3005, 2, '2024-01-21 14:30:00', 'Paid'),
(4003, 3002, 3, '2024-01-25 16:15:00', 'Pending'),
(4004, 3003, 4, '2024-02-05 10:45:00', 'Paid'),
(4005, 3004, 5, '2024-01-30 13:20:00', 'Waived');

-- Insert 5 SALE_ITEMS records
INSERT INTO sale_item (sale_item_id, sale_id, p_code, quantity,item_price) VALUES
(3001, 2001, 1001, 1, 59.99),   
(3002, 2002, 1003, 1, 299.99),  
(3003, 2002, 1002, 2, 69.99),   
(3004, 2003, 1002, 1, 69.99),   
(3005, 2004, 1004, 2, 69.99);  

INSERT INTO category (category_id, category_name) VALUES
(1, 'Games'),
(2, 'Consoles'),
(3, 'Accessories');

INSERT INTO membership (membership_id, membership_status, discount_rate) VALUES
(1, 'Non-member', 0),
(2, 'Standard', 5),
(3, 'Premium', 10);

INSERT INTO payment_status (status_id, status_name) VALUES
(1, 'Pending'),
(2, 'Paid'),
(3, 'Waived');


