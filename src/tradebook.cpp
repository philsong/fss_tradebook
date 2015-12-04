#include <fstream>
#include <iostream>
#include <sstream>
#include "tradebook.hpp"

using namespace std;

TradeBook::TradeBook(string db_name, int db_port, string symbols_file) : db {db_name, db_port} {
	parse_symbol_list(symbols_file);
}

TradeBook::~TradeBook() {}

void TradeBook::parse_symbol_list(string symbols_file) {
	// open file for reading
	ifstream ifs(symbols_file);
	if (!ifs) {
		cerr << "couldn't open" << symbols_file << " for reading.\n";
	} else {
		string inputLine;
		for (string inputLine; getline(ifs, inputLine); ) {
			string inputToken;
			istringstream lineStream(inputLine);
			struct symbol_info record;
			for (int csv_field = 0; getline(lineStream, inputToken, ','); csv_field++) {
				switch(csv_field) {
					case 0:
						record.symbol = inputToken;
						break;
					case 1:
						record.exchange = inputToken;
						break;
					case 2:
						record.name = inputToken;
						break;
					case 3:
						record.months = inputToken;
						break;
				}
			}
			symbols.push_back(record);
		}
	}

}

const vector<struct symbol_info>& TradeBook::get_futures() {
	return symbols;
}

const list<string> TradeBook::get_symbols() {
	list<string> result;
	for (auto& s : symbols) {
		result.push_back(s.symbol);
	}

	return result;
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
