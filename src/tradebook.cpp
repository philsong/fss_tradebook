#include <fstream>
#include <iostream>
#include <sstream>
#include "tradebook.hpp"

using namespace std;

TradeBook::TradeBook(string db_name, int db_port, string symbols_file) : db {db_name, db_port} {
	parse_symbol_list(symbols_file);
}

TradeBook::~TradeBook() {
	
}

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
					case 0: // SYMBOL
						// cout << "Case 0:\n"
						// 	 << "inputToken: " << inputToken << '\n';
						record.symbol = inputToken;
						break;
					case 1: // EXCHANGE
						record.exchange = inputToken;
						break;
					case 2: // CONTRACT NAME
						record.name = inputToken;
						break;
					case 3: // MONTHS AVAILABLE
						record.months = inputToken;
						break;
					case 4:
						symbolMap.emplace(inputToken, record);
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
		// Hardcoding CME into quandl_code as we only have CME data so far
		result.push_back("CME/" + s.symbol);
		// result.push_back(s.exchange + '/' + s.symbol);
	}

	return result;
}

const Contract TradeBook::get_contract(string quandl_code) {
	double lastPrice = 41.15;
	auto data = symbolMap[quandl_code];
	cout << "symbolMap[" << quandl_code << "].name: " << symbolMap[quandl_code].name << '\n';
	Contract result(data.symbol, data.name, data.exchange, lastPrice);
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
