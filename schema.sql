CREATE TABLE Traders(
	id int,
	uname text,
	name text,
	PRIMARY KEY(id)
);

CREATE TABLE Trade(
	id int,
	symbol text,
	expiry_date date,
	qt_lots int,
	price number, -- check precision of number
	tid int, -- trader id
	trade_time timestamp,
	PRIMARY KEY(id),
	FOREIGN KEY(tid) REFERENCES Traders(id)
);

-- option 1: trade type in trade table, secondary table for limit_order keeps
-- track of limit for a certain order_id

CREATE TABLE market_order(
	order_id serial PRIMARY KEY,
	symbol text,
	expiry_month int,
	expiry_year int,
	trader_id int FOREIGN KEY REFERENCES Traders(id),
	transaction_time timestamp,
	action -- buy / sell
);

CREATE TABLE limit_order(
	order_id serial PRIMARY KEY,
	symbol text,
	expiry_month int,
	expiry_year int,
	trader_id int FOREIGN KEY REFERENCES Traders(id),
	transaction_time timestamp,
	action -- buy / sell
);

CREATE TABLE pegged_order(
	order_id serial PRIMARY KEY,
	symbol text,
	expiry_month int,
	expiry_year int,
	trader_id int FOREIGN KEY REFERENCES Traders(id),
	transaction_time timestamp,
	action -- buy / sell
);

CREATE TABLE Fills(

);
