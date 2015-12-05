/**
 * \mainpage FSS TradeBook
 * \par Trade Book is a simple book of records system for commodity futures trades.
 * <a href="https://github.com/thePhilGuy/fss_tradebook">GitHub repository</a>
 */

#include "gui.hpp"
#include "tradebook.hpp"
#include "contract.hpp"

int main(int argc, char *argv[]) {

	// Create Qt Application object
	QApplication app(argc, argv);

	// Create Trade Book
	TradeBook book("tradeBookDB", 5432, "CMEGroup.csv");
	Contract::request_info("CME/CLH2015");

	// Create GUI and connect it to tradebook
	GUI interface(0, &book);
	interface.show();

	return app.exec();
}
