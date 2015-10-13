#include "trade.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Trade::Trade(string _symbol, int _quantity, double _price, bool _buy) : 
	symbol {_symbol}, 
	quantity {_quantity}, 
	price {_price}, 
	buy {_buy} {
}

Trade::~Trade() {}

string Trade::toSQL() {
	ostringstream sql;
	sql << "VALUES (" 
		<< "'" << symbol << "', "
		<< quantity << ", "
		<< price << ", "
		<< (buy ? "'true'" : "'false'") 
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