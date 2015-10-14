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

Aggregate::Aggregate(string _symbol, int _quantity, bool _buy, string _trader) :
	symbol {_symbol},
	quantity {_quantity},
	buy {_buy},
	trader_id {_trader} {
}

Aggregate::~Aggregate();

string Aggregate::toCSV() {
	ostringstream csv;
	csv << symbol << ", "
		<< quantity << ", "
		<< (buy ? "BUY, " : "SELL, ")
		<< trader_id
		<< "\n";

	return csv.str();
}

void Aggregate::add_position(int _qty, bool _buy) {

}

static void Aggregate::account_trade(vector<Aggregate>& v, string _symbol, string _trader, int _qty, bool _buy) {
	// check if (symbol, trader) is alread in container
	for (auto& p : v) {
		// (symbol, trader) found
		if (_symbol.compare(p.symbol) == 0 && _trader.compare(p.trader_id) == 0) {
			p.add_position(_qty, _buy);
			goto inserted;
		}
	}

	v.push_back(new Aggregate(_symbol, _trader, _qty, _buy));
	inserted:
}