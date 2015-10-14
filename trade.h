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

class Aggregate {
private:
	struct Position {
		int quantity;
		bool buy;
	};

	string trader_id;
	string symbol;
	vector<Position> positions;

public:
	Aggregate(string symbol, int quantity, bool buy, string trader_id);
	~Aggregate();
	string toCSV();
	static void account_trade(vector<Aggregate>& v, string symbol, string trader_id, int qty, bool buy);
}

#endif // TRADE_H
