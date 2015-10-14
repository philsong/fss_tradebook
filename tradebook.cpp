#include <fstream>
#include <iostream>
#include "tradebook.h"

using namespace std;

TradeBook::TradeBook(string db_name, int db_port) : db {db_name, db_port} {}

TradeBook::~TradeBook() {}

void TradeBook::record_trade(Trade & data) {
	db.insert(data);
}

void TradeBook::download_csv(string file_target) {
	vector<Trade> trades = db.get_all();
	ofstream ofs(file_target);
	if (!ofs) {
		cerr << "couldn't open " << file_target << " for writing.\n";
	} else {
		for (auto& t : trades) ofs << t.toCSV();
	}
}