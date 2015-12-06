#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <string>

using namespace std;

class Contract{
private:
	string symbol; /// Symbol for future contract
	string name; /// Human Readable name
	string exchange; /// Exchange the data is from
	double lastPrice; /// Latest price available

public:
	/**
	 * Constructor
	 * Constructs a Contract object
	 * \param s Contract symbol (eg HH, HP, G4)
	 * \param n Contract Name
	 * \param e Exchange the data is from
	 * \param p Latest price to build with
	 */
	Contract(string s, string n, string e, double p);
	// ~Contract();

	/// Request price info from QUANDL API
	static void request_info(string quandl_code);
    string get_name();
	double get_last_price();
    string toString();
};

#endif // CONTRACT_HPP
