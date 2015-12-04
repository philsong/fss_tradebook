/**
 * \class TradeBook
 *
 * \brief Book of records system for trades
 *
 * This class defines the tradebook system. Connecting the database with
 the GUI, this class orchestrates Trade data insertion and downloads
 as CSV files.
 */

#ifndef TRADEBOOK_H
#define TRADEBOOK_H

#include <string>
#include <list>
#include "database.hpp"
#include "trade.hpp"

using namespace std;

struct symbol_info {
	string symbol;
	string exchange;
	string name;
	string months;
};

class Contract {
private:
	string symbol,
	string exchange,
	double currentPrice

public:
	Contract();
	~Contract() = 0;
	static const Contract& request_info(string symbol);
	double get_last_price();
}

class TradeBook {
private:
	/// The Database controller object which holds the Trades table.
	Database db;

  /// The FIX Client object which interacts with an exchange
  // FixClient fc;

	// List of available symbols
	vector<struct symbol_info> symbols;

	void parse_symbol_list(string symbols_file);

public:
	/// Constructor for a TradeBook, parameters are for the Database.
	TradeBook(string db_name, int db_port, string symbols_file);
	~TradeBook();
   /**
    * Insert Trade into the Database db
    * \param data Reference to Trade to be inserted
    */
	void record_trade(Trade & data);
   /**
    * Download all trades as CSV
    * \param file_target Name of file to save output.
    */
	void download_csv(string file_target);
   /**
    * Download aggregate positions as CSV
    * \param file_target Name of file to save output.
    */
	void download_aggregate_csv(string file_target);

	const list<string> get_symbols();
	const vector<struct symbol_info>& get_futures();

};

#endif // TRADEBOOK_H
