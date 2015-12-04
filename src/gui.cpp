#include "gui.hpp"

#include <iostream>

GUI::GUI(QWidget *parent, TradeBook * tb)
    : QMainWindow(parent) {
    // Connect GUI to TradeBook
    book = tb;

    // Get list of symbols from Tradebook
    for (auto& s : tb->get_symbols())
        symbols.append(s.c_str());

    // Set size and title of window
	setFixedSize(1000, 800);
	setWindowTitle("FSS TradeBook");

    // *** MENU BAR ***
	// Create and configure file menu
	fileMenu = menuBar()->addMenu(tr("&File"));
	downloadAct = new QAction(tr("Download &all trades"), this);
	downloadAggregateAct = new QAction(tr("Download &aggregate positions"), this);
	fileMenu->addAction(downloadAct);
	fileMenu->addAction(downloadAggregateAct);
    // Connect download actions
	connect(downloadAct, SIGNAL(triggered()), this, SLOT (slotDownload()));
	connect(downloadAggregateAct, SIGNAL(triggered()), this, SLOT (slotAggregateDownload()));

    // Create and configure settings menu
    settingsMenu = menuBar()->addMenu(tr("&Settings"));
    // importAct = new QAction(tr("Import settings from file..."), this);


    // *** NEW ORDER FORM ***
	// Symbol Field
	symbolLabel = new QLabel("Symbol: ", this);
	symbolLabel->setGeometry(10, 40, 150, 40);
	symbolEdit = new QComboBox(this);
	symbolEdit->addItems(symbols);
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

	// Trade Type Field
	tradeTypeLabel = new QLabel("Trade type: ", this);
	tradeTypeLabel->setGeometry(10, 290, 150, 40);
	tradeTypeEdit = new QComboBox(this);
	QStringList tradeTypes;
	tradeTypes.append("Market");
	tradeTypes.append("Limit");
	tradeTypes.append("Pegged");
	tradeTypeEdit->addItems(tradeTypes);
	tradeTypeEdit->setGeometry(170, 290, 410, 40);

	// Limit for limit orders
	limitLabel = new QLabel("Price Limit", this);
	limitLabel->setGeometry(10, 340, 150, 40);
	limitEdit = new QLineEdit(this);
	limitEdit->setGeometry(170, 340, 410, 40);

	// Expiration date field
	expLabel = new QLabel("Contract expiry: ", this);
	expLabel->setGeometry(10, 390, 580, 40);
	expDate = new QDateEdit(this);
	expDate->setGeometry(10, 440, 580, 40);
	expDate->setDisplayFormat("MM/dd/yyyy");

	// Transaction time and date
	transactionLabel = new QLabel("Transaction time: ", this);
	transactionLabel->setGeometry(10, 490, 580, 40);
	transactionDateTime = new QDateTimeEdit(this);
	transactionDateTime->setGeometry(10, 540, 580, 40);
	transactionDateTime->setDisplayFormat("MM/dd/yyyy HH:mm:ss");

	// Create and position submit button
	submitButton = new QPushButton("Submit", this);
	submitButton->setGeometry(490, 640, 100, 40);

	// Connect submit button
	connect(submitButton, SIGNAL(clicked()), this, SLOT (slotSubmission()));
}

GUI::~GUI() {
	delete downloadAct;
	delete downloadAggregateAct;
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
	string symbol = symbolEdit->currentText().toStdString();
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
		tr("Download All Trades"), "", tr("CSV File (*.csv)")).toStdString();

	book->download_csv(save_file);
}

void GUI::slotAggregateDownload() {
	string save_file = QFileDialog::getSaveFileName(this,
		tr("Download Aggregate Positions"), "", tr("CSV File (*.csv)")).toStdString();

	book->download_aggregate_csv(save_file);
}
