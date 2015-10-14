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
	void record_trade(Trade & data);
	void download_csv(string file_target);

};

#endif // TRADEBOOK_H
