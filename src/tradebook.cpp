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
			symbol_info commodity_info;
			for (int csv_field = 0; getline(lineStream, inputToken, ','); csv_field++) {
				switch(csv_field) {
					case 0:
						commodity_info.symbol = inputToken;
						break;
					case 1:
						commodity_info.exchange = inputToken;
						break;
					case 2:
						commodity_info.name = inputToken;
						break;
					case 3:
						commodity_info.months = inputToken;
						break;
				}
			}

			commodities.push_back(commodity_info);
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
