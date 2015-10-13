#ifndef TRADE_H
#define TRADE_H

#include <string>

using namespace std;

class Trade {
private:
	string symbol;
	int quantity;
	double price;
	bool buy;

public:
	Trade(string _symbol, int _quantity, double _price, bool _buy);
	~Trade();
	string toSQL();
	string toCSV();
};

#endif // TRADE_H
