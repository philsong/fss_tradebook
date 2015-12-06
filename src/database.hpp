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
#include "trade.hpp"

using namespace std;
using namespace pqxx;

class Database {
private:
	connection* db_connection; ///
public:
	/// Construct a Database object from a name and port
	Database(string db_name, int port);
	~Database();

   /**
	* Insert a Order into the database
	* \param data a reference to the Order object entered.
	*/
	void insert(Order & data);
	/**
 	* Insert a LimitOrder into the database
 	* \param data a reference to the Order object entered.
 	*/
	void insert(LimitOrder & data);
	/**
 	* Insert a PeggedOrder into the database
 	* \param data a reference to the Order object entered.
 	*/
	void insert(PeggedOrder & data);

	/// Get all trades in the trade table
	vector<Order> get_all();

   /**
    * Get all aggregate positions in the trade table
    * This method accounts for each trade with the same trader and symbol
    * and combines them into an Aggregate object.
    * \return An std::vector of Aggregate objects.
    */
	vector<Aggregate> get_aggregates();
};

#endif // DATABASE_H
