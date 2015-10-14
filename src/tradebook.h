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
#include "database.h"
#include "trade.h"

using namespace std;

class TradeBook {
private:
	/// The Database member object which holds the Trades table.
	Database db;

public:
	/// Constructor for a TradeBook, parameters are for the Database.
	TradeBook(string db_name, int db_port);
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
};

#endif // TRADEBOOK_H
