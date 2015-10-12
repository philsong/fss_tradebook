#ifndef TRADE_H
#define TRADE_H

#include "database.h"
#include <string>

using namespace std;

class TradeBook {
private:
	Database db;

public:
	TradeBook(string db_name, int db_port);
	~TradeBook();
};

#endif // TRADE_H
