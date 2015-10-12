#include "trade.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Trade::Trade(string _symbol, int _quantity, double _price) : 
symbol {_symbol}, quantity {_quantity}, price {_price} { }

Trade::~Trade() {}

string Trade::toSQL() {
	ostringstream sql;
	sql << "VALUES (" 
		<< "'" << symbol << "', "
		<< quantity << ", "
		<< price 
		<< ");";

	return sql.str();
}