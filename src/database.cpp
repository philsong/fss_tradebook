#include "database.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using namespace pqxx;

Database::Database(string db_name, int port) {
	// Format the pqxx config string
	ostringstream config_stream;
	config_stream << "dbname=" << db_name
				  << " user=postgres hostaddr=127.0.0.1" 
				  << " port=" << port;
	string config_string = config_stream.str();

	// Connect to postgreSQL database
	try {
		db_connection = new connection(config_string);
		if (db_connection->is_open()) {
			cout << "Opened database succesfully!\n";
		} else {
			cout << "Couldn't open database.\n";
		}
	} catch (const exception &e) {
		cerr << e.what() << endl;
	}
}

Database::~Database() {
	cout << "Disconnecting from database.\n";
	db_connection->disconnect();
	delete db_connection;
}

void Database::insert(Trade & data) {
	// Format SQL insert query
	ostringstream query_stream;
	query_stream << "INSERT INTO "
				 << "Trades(symbol, qt_lots, price, buy, "
				 <<		   "expiry, transaction_dt, trader_id) "
				 << data.toSQL();
	string query = query_stream.str();

	// Reminder: try / catch
	cout << query << "\n";

	// Create postgreSQL transaction object
	work transaction(*db_connection); 

	// Execute query
	transaction.exec(query);
	transaction.commit();
	cout << "Record created.\n";
}

vector<Trade> Database::get_all() {
	// Format SQL select query
	string query("SELECT * FROM Trades;");

	// Create postgreSQL nontransaction object
	nontransaction ntransaction(*db_connection);

	// Execute query
	result db_trades(ntransaction.exec(query));


	vector<Trade> trades {};
	for (auto trade = db_trades.begin(); trade != db_trades.end(); ++trade) {
		Trade temp(
			trade[0].as<string>(), //Symbol
			trade[1].as<int>(), //Qty
			trade[2].as<double>(), //Price
			trade[3].as<bool>(), //Buy
			trade[4].as<string>(), //Expiry
			trade[5].as<string>(), //DateTime
			trade[6].as<string>() //Trader
		);
		trades.push_back(temp);
	}

	return trades;
}

vector<Aggregate> Database::get_aggregates() {
	// Format SQL select query
	string query("SELECT buy, qt_lots, symbol, trader_id FROM Trades;");

	// Create postgreSQL nontransaction object
	nontransaction ntransaction(*db_connection);

	// Execute query
	result db_trades(ntransaction.exec(query));

	vector<Aggregate> trades {};
	for (auto trade = db_trades.begin(); trade != db_trades.end(); ++trade) {
		bool   buy       = trade[0].as<bool>();
		int    qty       = trade[1].as<int>();
		string symbol    = trade[2].as<string>();
		string trader_id = trade[3].as<string>();
		Aggregate::account_trade(trades, symbol, trader_id, qty, buy);
	}

	return trades;
}