#include "gui.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent) {
    // Set size and title of window
	setFixedSize(600, 400);
	setWindowTitle("FSS TradeBook");

	// Create and position submit button
	submitButton = new QPushButton("Submit", this);
	submitButton->setGeometry(490, 350, 100, 40);

	// Connect submit button
	connect(submitButton, SIGNAL(clicked()), QApplication::instance(), SLOT (quit())); // to QUIT application for now.
}

GUI::~GUI() {

}
