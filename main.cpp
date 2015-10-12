#include "gui.h"
#include "trade.h"

int main(int argc, char *argv[]) {

	// Create Qt Application object
	QApplication app(argc, argv);

	// Create Trade Book
	TradeBook book("tradeBookDB", 5432);

	// Create GUI and connect it to tradebook
	GUI interface;
	interface.show();

	return app.exec();
}
