#ifndef TRADEBOOK_H
#define TRADEBOOK_H

#include <string>
#include "database.h"
#include "trade.h"

using namespace std;

class TradeBook {
private:
	Database db;

public:
	TradeBook(string db_name, int db_port);
	~TradeBook();
	void record_trade(string symbol, int qty, double price);
	void download_csv(string file_target);

};

#endif // TRADEBOOK_H
