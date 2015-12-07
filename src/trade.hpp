#ifndef TRADE_H
#define TRADE_H

#include <string>
#include <vector>

using namespace std;

/**
 * \class Order
 *
 * \brief Order data representation
 *
 * This class defines a trade of a future commodity as well as database and file
   operations formatting.
 */
class Order {
private:
	bool buy; /// true if the trade is a buy, false if a sell
	int quantity; /// # of shares bought
	string expiration_date; /// expiration date of the future
	string symbol; /// the symbol for the commodity being traded
	string trader_id; /// a unique ID for a trader
	string transaction_datetime; /// the time and date when the trade is executed
	int order_type = 0; /// Market 0 - Limit 1 - Pegged 2 - Interest 3
public:
   /**
    * Constructor
    * Constructs a Order object
    * \param s Contract symbol (eg HH, HP, G4)
    * \param q # Lots
    * \param b Buy (true) or Sell (false) type of trade
    * \param exp Contract expiry (eg Dec 2019)
    * \param trader Trader who executed trade.
    */
	Order(string s, int q, bool b, string exp, string trader);
	~Order();
	/// Order data in SQL insert query format VALUES (field, ...)
	virtual string toSQL();
	/// Order data in CSV line format
	virtual string toCSV();
};

class LimitOrder : public Order {
private:
	double limitPrice; /// Price at which the trade should be executed
public:
	/**
	 * Constructor
	 * Constructs a LimitOrder object
	 * \param s Contract symbol (eg HH, HP, G4)
	 * \param q # Lots
	 * \param p Limit price
	 * \param b Buy (true) or Sell (false) type of trade
	 * \param exp Contract expiry (eg Dec 2019)
	 * \param trader Trader who executed trade.
	 */
	LimitOrder(string s, int q, double p, bool b, string exp, string trader);
	string toCSV();
	string toSQL();
};

class PeggedOrder : public Order {
public:
	PeggedOrder(string s, int q, bool b, string exp, string t);
	string toCSV();
	string toSQL();
};

class InterestSwapOrder : public Order {
	// buy is irrelevant
	// symbol is the floating rate used
private:
	bool paysFixed;
	double floatingSpread;
	string clearingHouse;
public:
	InterestSwapOrder();
	string toCSV();
	string toSQL();
}

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
