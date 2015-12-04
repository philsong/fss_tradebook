#include <fstream>
#include <iostream>
#include <sstream>
#include "tradebook.h"

using namespace std;

TradeBook::TradeBook(string db_name, int db_port) : db {db_name, db_port} {}

TradeBook::~TradeBook() {}

void TradeBook::parse_symbol_list(string symbols_file) {
	// open file for reading
	ifstream ifs(symbols_file);
	if (!ifs) {
		cerr << "couldn't open" << symbols_file << " for reading.\n";
	} else {
		string inputLine;
		for (string inputLine; getline(ifs, inputLine); ) {
			// Each SYMBOL LINE
			string inputToken;
			cout << inputLine << '\n';
			int i = 0;
			istringstream lineStream(inputLine);
			while (getline(lineStream, inputToken, ',')) {
			// Each SYMBOL TOKEN
				/* new symbol =
						symbol: 0,
						exchange: 1,
						name: 2,
						months: 3,
						api_code: 4
				*/
				cout << i++ << ": " << inputToken << '\n';
			}
		}
	}
}

void TradeBook::record_trade(Trade & data) {
	db.insert(data);
}

void TradeBook::download_csv(string file_target) {
	vector<Trade> trades = db.get_all();
	ofstream ofs(file_target);
	if (!ofs) {
		cerr << "couldn't open " << file_target << " for writing.\n";
	} else {
		ofs << "Symbol, Lots, Price, Buy/Sell, Contract Expiry, Transaction Date, Trader\n";
		for (auto& t : trades) ofs << t.toCSV();
	}
}

void TradeBook::download_aggregate_csv(string file_target) {
	vector<Aggregate> traders = db.get_aggregates();
	ofstream ofs(file_target);
	if (!ofs) {
		cerr << "couldn't open " << file_target << " for writing.\n";
	} else {
		ofs << "Symbol, Lots, Buy/Sell, Trader\n";
		for (auto& a : traders) ofs << a.toCSV();
	}
}
