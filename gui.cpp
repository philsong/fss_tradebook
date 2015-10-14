#include "gui.h"

#include <iostream>

GUI::GUI(QWidget *parent, TradeBook * tb)
    : QMainWindow(parent) {
    // Connect GUI to TradeBook
    book = tb;

    // Set size and title of window
	setFixedSize(600, 700);
	setWindowTitle("FSS TradeBook");

	// Create and configure menu bar
	downloadAct = new QAction(tr("&Download trades"), this);
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(downloadAct);

	// Connect download action
	connect(downloadAct, SIGNAL(triggered()), this, SLOT (slotDownload()));

	// Symbol Field
	symbolLabel = new QLabel("Symbol: ", this);
	symbolLabel->setGeometry(10, 40, 150, 40);
	symbolEdit = new QLineEdit(this);
	symbolEdit->setGeometry(170, 40, 410, 40);

	// Price Field
	priceLabel = new QLabel("Price: ", this);
	priceLabel->setGeometry(10, 90, 150, 40);
	priceEdit = new QLineEdit(this);
	priceEdit->setGeometry(170, 90, 410, 40);

	// Qty Field
	qtyLabel = new QLabel("Quantity: ", this);
	qtyLabel->setGeometry(10, 140, 150, 40);
	qtyEdit = new QLineEdit(this);
	qtyEdit->setGeometry(170, 140, 410, 40);

	// Trader Field
	traderLabel = new QLabel("Trader id: ", this);
	traderLabel->setGeometry(10, 190, 150, 40);
	traderEdit = new QLineEdit(this);
	traderEdit->setGeometry(170, 190, 410, 40);

	// Create and position buy / sell buttons
	buyButton = new QRadioButton("Buy", this);
	buyButton->setGeometry(10, 240, 280, 40);
	buyButton->setChecked(true);
	sellButton = new QRadioButton("Sell", this);
	sellButton->setGeometry(300, 240, 280, 40);

	// Expiration date field
	expLabel = new QLabel("Contract expiry: ", this);
	expLabel->setGeometry(10, 290, 580, 40);
	expDate = new QDateEdit(this);
	expDate->setGeometry(10, 340, 580, 40);
	expDate->setDisplayFormat("dd/MM/yyyy");

	// Transaction time and date
	transactionLabel = new QLabel("Transaction time: ", this);
	transactionLabel->setGeometry(10, 390, 580, 40);
	transactionDateTime = new QDateTimeEdit(this);
	transactionDateTime->setGeometry(10, 440, 580, 40);
	transactionDateTime->setDisplayFormat("dd/MM/yyyy HH:mm:ss");

	// Create and position submit button
	submitButton = new QPushButton("Submit", this);
	submitButton->setGeometry(490, 640, 100, 40);

	// Connect submit button
	connect(submitButton, SIGNAL(clicked()), this, SLOT (slotSubmission()));
}

GUI::~GUI() { 
	delete downloadAct;
	delete fileMenu;
	delete priceEdit;
	delete priceLabel;
	delete qtyEdit;
	delete qtyLabel;
	delete submitButton;
	delete symbolEdit;
	delete symbolLabel;
	delete traderEdit;
	delete traderLabel;
	delete transactionDateTime;
	delete transactionLabel;
}

void GUI::slotSubmission() {
	// Text fields
	string symbol = symbolEdit->text().toStdString();
	string price_string = priceEdit->text().toStdString();
	string qty_string = qtyEdit->text().toStdString();
	string trader = traderEdit->text().toStdString();
	string expiry = expDate->date().toString().toStdString();
	string datetime = transactionDateTime->dateTime().toString().toStdString();

	cout << "Expiry: " << expiry << "\n Datetime: " << datetime << "\n"; 

	// Radio buttons
	bool buy = buyButton->isChecked();
	bool sell = sellButton->isChecked();
	if (!(buy || sell)) {
		// emit must pick buy or sell signal
		cerr << "Must pick one of buy or sell\n";
		return;
	}

	try {
		double price = stod(price_string);
		int qty = stoi(qty_string);
		Trade tmp(symbol, qty, price, buy, expiry, datetime, trader);
		book->record_trade(tmp);
	} catch (const invalid_argument &ia) {
		// emit invalid argument signal
		cerr << "Invalid argument: " << ia.what() << "\n";
	}
}

void GUI::slotDownload() {
	string save_file = QFileDialog::getSaveFileName(this,
		tr("Save as CSV"), "", tr("CSV File (*.csv)")).toStdString();

	book->download_csv(save_file);
}