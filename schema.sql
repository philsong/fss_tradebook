CREATE TABLE Trade(
	trade_id serial,
	trader_id text,
	symbol text,
	expiry_date date,
	qt_lots int,
	price decimal,
	trade_time text,
	PRIMARY KEY(trade_id)
);

CREATE TABLE Order_(
	order_id serial,
	symbol text,
	expiry_date text,
	action boolean,
	trader_id text,
	transaction_dt text,
	order_type int, -- 0: market, 1: limit, 2: pegged
	PRIMARY KEY(order_id)
);

CREATE TABLE Order_limit(
	order_id int,
	price_limit decimal,
    FOREIGN KEY(order_id) REFERENCES Order_(order_id)
);

CREATE TABLE Fill(
	fill_id serial,
	order_id int,
	qt_lots int,
	transaction_dt text,
	price decimal,
	PRIMARY KEY(fill_id),
	FOREIGN KEY(order_id) REFERENCES Order_(order_id)
);

CREATE TABLE SwapOrder(
	swap_id serial,
	amount decimal,
	floating_rate decimal,
	floating_spread decimal,
	fixed_rate decimal,
	start_date text,
	expiry_date text,
	pays_floating boolean,
	PRIMARY KEY(swap_id)
)

CREATE TABLE SwapFills(
	fill_id serial,
	swap_ip int,
	PRIMARY KEY(fill_id),
	FOREIGN KEY(swap_id) REFERENCES SwapOrder(order_id)
)
