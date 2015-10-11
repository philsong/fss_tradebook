#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class Database {
private:
	connection* db_connection;
public:
	Database(string db_name, int port);
	~Database();
};

#endif // DATABASE_H