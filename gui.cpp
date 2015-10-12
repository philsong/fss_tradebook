#include "gui.h"

#include <iostream>

GUI::GUI(QWidget *parent, TradeBook * tb)
    : QMainWindow(parent) {
    // Connect GUI to TradeBook
    book = tb;

    // Set size and title of window
	setFixedSize(600, 400);
	setWindowTitle("FSS TradeBook");

	// Symbol Field
	symbolLabel = new QLabel("Symbol: ", this);
	symbolLabel->setGeometry(10, 10, 100, 40);
	symbolEdit = new QLineEdit(this);
	symbolEdit->setGeometry(120, 10, 150, 40);

	// Price Field
	priceLabel = new QLabel("Price: ", this);
	priceLabel->setGeometry(10, 60, 100, 40);
	priceEdit = new QLineEdit(this);
	priceEdit->setGeometry(120, 60, 150, 40);

	// Qty Field
	qtyLabel = new QLabel("Quantity: ", this);
	qtyLabel->setGeometry(10, 110, 100, 40);
	qtyEdit = new QLineEdit(this);
	qtyEdit->setGeometry(120, 110, 150, 40);

	// Create and position submit button
	submitButton = new QPushButton("Submit", this);
	submitButton->setGeometry(490, 350, 100, 40);

	// Connect submit button
	connect(submitButton, SIGNAL(clicked()), this, SLOT (slotSubmission())); // to QUIT application for now.
}

GUI::~GUI() {
	delete symbolLabel;
	delete symbolEdit;

	delete priceLabel;
	delete priceEdit;

	delete qtyLabel;
	delete qtyEdit;

	delete submitButton;
}

void GUI::slotSubmission() {
	string symbol = symbolEdit->text().toStdString();
	string price_string = priceEdit->text().toStdString();
	string qty_string = qtyEdit->text().toStdString();

	try {
		double price = stod(price_string);
		int qty = stoi(qty_string);
		book->record_trade(symbol, qty, price);
	} catch (const invalid_argument &ia) {
		// emit invalid argument signal
		cerr << "Invalid argument: " << ia.what() << "\n";
	}

}