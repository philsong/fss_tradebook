#ifndef TRADE_H
#define TRADE_H

#include <string>
#include <vector>

using namespace std;

/**
 * \class Trade
 *
 * \brief Trade data representation
 *
 * This class defines a trade of a future commodity as well as database and file 
   operations formatting.
 */
class Trade {
private:
	bool buy;
	double price;
	int quantity;
	string expiration_date;
	string symbol;
	string trader_id;
	string transaction_datetime;

public:
   /**
    * Constructor
    * Constructs a Trade object
    * \param _symbol Contract symbol (eg HH, HP, G4)
    * \param _quantity # Lots
    * \param _price Price per lot
    * \param _buy Buy (true) or Sell (false) type of trade
    * \param _expiration_date Contract expiry (eg Tue Dec 31 2019)
    * \param _transaction_dt Date and Time of transaction. ( eg Tue Oct 13 21:26:00 2015 )
    * \param _trader Trader who executed trade.
    */
	Trade(string _symbol, int _quantity, double _price, bool _buy, 
		  string _expiration_date, string _transaction_dt, string _trader);
	~Trade();
	/// Trade data in SQL insert query format VALUES (field, ...)
	string toSQL();
	/// Trade data in CSV line format
	string toCSV();
};

/**
 * \class Aggregate
 *
 * \brief Aggregation of trades on one commodity by a single trader.
 *
 * This class defines the aggregate position of a trader on a single commodity.
 It consists of an underlying collection of Positions, which include the number of
 lots in the trade and whether it is a buy or sell operation. 
 */
class Aggregate {
private:
	struct Position {
		int quantity;
		bool buy;
	};

	string symbol;
	string trader_id;
	vector<Position> positions;

public:
	/// Constructor for Aggregate object with an initial position (quantity, buy)
	Aggregate(string symbol, string trader_id, int quantity, bool buy);
	~Aggregate();
	/// Aggregate position data in CSV line format
	string toCSV();
   /**
    * Account for trade in collection of Aggregate objects
    * This function will add the position supplied to the (trader, symbol) pair if it exists in v,
    Otherwise a new Aggregate will be created and inserted at the end of container v.
    * \param v Collection of aggregate positions to be updated.
    * \param symbol Contract symbol
    * \param trader_id Trader who executed trade
    * \param qty # Lots
    * \param buy Buy (true) or Sell (false) type of trade
    */
	static void account_trade(vector<Aggregate>& v, string symbol, string trader_id, int qty, bool buy);
	/// Add single trade to Aggregate position
	void add_position(int quantity, bool buy);
};

#endif // TRADE_H
