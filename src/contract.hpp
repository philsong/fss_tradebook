#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <string>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

using namespace std;

class Contract : public QObject {
    Q_OBJECT
private:
	string symbol;
	string name;
	string exchange;
	double lastPrice;

public:
	// Contract(string symbol_, string name_, string exchange_, double price);
	// ~Contract();
	static void request_info(string quandl_code);
	// double get_last_price();
};

#endif // CONTRACT_HPP
