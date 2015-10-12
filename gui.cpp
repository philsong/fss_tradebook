#include "gui.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent) {
    // Set size and title of window
	setFixedSize(600, 400);
	setWindowTitle("FSS TradeBook");

	// Create and position symbol field
	symbolLabel = new QLabel("Symbol: ", this);
	symbolLabel->setGeometry(10, 10, 100, 40);
	symbolEdit = new QLineEdit(this);
	symbolEdit->setGeometry(120, 10, 150, 40);

	// Create and position submit button
	submitButton = new QPushButton("Submit", this);
	submitButton->setGeometry(490, 350, 100, 40);

	// Connect submit button
	connect(submitButton, SIGNAL(clicked()), QApplication::instance(), SLOT (quit())); // to QUIT application for now.
}

GUI::~GUI() {
	delete symbolLabel;
	delete symbolEdit;
	delete submitButton;
}

GUI::slotSubmitButtonClicked() {
	
}