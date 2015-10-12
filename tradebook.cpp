#include "tradebook.h"

using namespace std;

TradeBook::TradeBook(string db_name, int db_port) : db {db_name, db_port} {}

TradeBook::~TradeBook() {}

void TradeBook::record_trade(string symbol, int qty, double price) {
	Trade temp(symbol, qty, price);
	db.insert(temp);
}
