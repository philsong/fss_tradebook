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

CREATE TABLE market_order(

);

CREATE TABLE limit_order(

);

CREATE TABLE pegged_order(

);
