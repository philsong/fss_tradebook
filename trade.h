#ifndef TRADE_H
#define TRADE_H

#include <string>

using namespace std;

class Trade {
private:
	string symbol;
	int quantity;
	double price;

public:
	Trade(string _symbol, int _quantity, double _price);
	~Trade();
	string toSQL();
};

#endif // TRADE_H
