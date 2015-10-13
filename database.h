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
	Database(string db_name, int port);
	~Database();
	void insert(Trade data);
	vector<Trade> get_all();
};

#endif // DATABASE_H