#ifndef TRADE_H
#define TRADE_H

#include <string>

using namespace std;

class Trade {
private:
	bool buy;
	double price;
	int quantity;
	string expiration_date;
	string symbol;
	string trader_id;
	string transaction_datetime;

public:
	Trade(string _symbol, int _quantity, double _price, bool _buy, 
		  string _expiration_date, string _transaction_dt, string _trader);
	~Trade();
	string toSQL();
	string toCSV();
};

#endif // TRADE_H
