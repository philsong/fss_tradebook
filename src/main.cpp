/**
 * \mainpage FSS TradeBook
 * \par Order Book is a simple book of records system for commodity futures trades.
 * <a href="https://github.com/thePhilGuy/fss_tradebook">GitHub repository</a>
 */

#include "gui.hpp"
#include "tradebook.hpp"
#include "contract.hpp"

static int exchange_pid;
/// Function execs the exchange and keeps track of its pid
void start_exchange() {
	//fork

	// child
		// exec("python27 fixpy/executor/executor.py")

	// parent
		// store pid into exchange_pid;
}

int main(int argc, char *argv[]) {

	// Create Qt Application object
	QApplication app(argc, argv);

	// Create Order Book
	TradeBook book("tradeBookDB", 5432, "CMEGroup.csv");

	// Exec test exchange
	start_exchange();

	// Create GUI and connect it to tradebook
	GUI interface(0, &book);
	interface.show();

	return app.exec();
}
