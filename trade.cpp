#include "trade.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Trade::Trade(string _symbol, int _quantity, double _price, bool _buy, 
		     string _expiration_date, string _transaction_dt, string _trader) : 
	buy {_buy},
	price {_price}, 
	quantity {_quantity}, 
	expiration_date {_expiration_date},
	symbol {_symbol}, 
	trader_id {_trader}, 
	transaction_datetime {_transaction_dt} {
}

Trade::~Trade() {}

string Trade::toSQL() {
	ostringstream sql;
	sql << "VALUES (" 
		<< "'" << symbol << "', "
		<< quantity << ", "
		<< price << ", "
		<< (buy ? "'true', " : "'false', ")
		<< "'" << expiration_date << "', "
		<< "'" << transaction_datetime << "', "
		<< "'" << trader_id << "'" 
		<< ");";

	return sql.str();
}

string Trade::toCSV() {
	ostringstream csv;
	csv << symbol << ", "
		<< quantity << ", "
		<< price << ", "
		<< (buy ? "BUY" : "SELL")
		<< "\n";

	return csv.str();
}	