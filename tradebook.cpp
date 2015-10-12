#include "tradebook.h"

using namespace std;

TradeBook::TradeBook(string db_name, int db_port) : db {db_name, db_port} {}

TradeBook::~TradeBook() {}