/**
 * \class Database
 *
 * \brief Interface to underlying database.
 *
 * This class is meant to provide an interface to the underlying PostgreSQL
 * database. It provides functionality to insert and retrieve trades.
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include "trade.h"

using namespace std;
using namespace pqxx;

class Database {
private:
	connection* db_connection;
public:
	/// Construct a Database object from a name and port
	Database(string db_name, int port);
	~Database();

   /**
	* Insert a Trade into the database
	* \param data a reference to the Trade object entered.
	*/
	void insert(Trade & data);

	/// Get all trades in the trade table
	vector<Trade> get_all();

   /** 
    * Get all aggregate positions in the trade table
    * This method accounts for each trade with the same trader and symbol
    * and combines them into an Aggregate object.
    * \return An std::vector of Aggregate objects.
    */
	vector<Aggregate> get_aggregates();
};

#endif // DATABASE_H