#include "gui.h"
#include "tradebook.h"

int main(int argc, char *argv[]) {

	// Create Qt Application object
	QApplication app(argc, argv);

	// Create Trade Book
	TradeBook book("tradeBookDB", 5432);

	// Create GUI and connect it to tradebook
	GUI interface(0, &book);
	interface.show();

	return app.exec();
}
