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