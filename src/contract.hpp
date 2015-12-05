#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <string>

using namespace std;

class Contract{
private:
	string symbol;
	string name;
	string exchange;
	double lastPrice;

public:
	Contract(string s, string n, string e, double p);
	// ~Contract();
	static void request_info(string quandl_code);
    string get_name();
	double get_last_price();
};

#endif // CONTRACT_HPP
