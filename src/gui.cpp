#include "gui.hpp"

#include <iostream>

GUI::GUI(QWidget *parent, TradeBook * tb)
    : QMainWindow(parent) {
    // Connect GUI to TradeBook
    book = tb;

    // Get list of symbols from Tradebook
    for (auto& s : book->get_symbols())
        symbols.append(s.c_str());

    // Set size and title of window
	setFixedSize(1000, 800);
	setWindowTitle("FSS TradeBook");

    // *** MENU BAR ***
	// Create and configure file menu
	fileMenu = menuBar()->addMenu(tr("&Reports"));
	downloadAllAct = new QAction(tr("&All trades"), this);
	downloadAggregateAct = new QAction(tr("&Aggregate positions"), this);
    downloadPLAct = new QAction(tr("&Profit and Loss"), this);
    downloadDetailedPLAct = new QAction("Detailed Profit and Loss", this);
	fileMenu->addAction(downloadAllAct);
	fileMenu->addAction(downloadAggregateAct);
    fileMenu->addAction(downloadPLAct);
    fileMenu->addAction(downloadDetailedPLAct);
    // Connect download actions
	connect(downloadAllAct, SIGNAL(triggered()), this, SLOT (slotDownload()));
	connect(downloadAggregateAct, SIGNAL(triggered()), this, SLOT (slotAggregateDownload()));

    // Create and configure settings menu
    settingsMenu = menuBar()->addMenu(tr("&Settings"));
    // importAct = new QAction(tr("Import settings from file..."), this);


    // *** NEW ORDER FORM *** ==================================================
	// Symbol Field
	symbolLabel = new QLabel("Symbol: ", this);
	symbolLabel->setGeometry(10, 40, 150, 40);
	symbolEdit = new QComboBox(this);
	symbolEdit->addItems(symbols);
	symbolEdit->setGeometry(170, 40, 310, 40);
    // Connect change in symbolEdit to displaying a current contract
    connect(symbolEdit, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slotHandleSymbolChange(const QString&)));

	// Price Field
	priceLabel = new QLabel("Price: ", this);
	priceLabel->setGeometry(10, 90, 150, 40);
	priceEdit = new QLineEdit(this);
	priceEdit->setGeometry(170, 90, 310, 40);

	// Qty Field
	qtyLabel = new QLabel("Quantity: ", this);
	qtyLabel->setGeometry(10, 140, 150, 40);
	qtyEdit = new QLineEdit(this);
	qtyEdit->setGeometry(170, 140, 310, 40);

	// Trader Field
	traderLabel = new QLabel("Trader id: ", this);
	traderLabel->setGeometry(10, 190, 150, 40);
	traderEdit = new QLineEdit(this);
	traderEdit->setGeometry(170, 190, 310, 40);

	// Create and position buy / sell buttons
	buyButton = new QRadioButton("Buy", this);
	buyButton->setGeometry(10, 240, 280, 40);
	buyButton->setChecked(true);
	sellButton = new QRadioButton("Sell", this);
	sellButton->setGeometry(300, 240, 280, 40);

	// Order Type Field
	tradeTypeLabel = new QLabel("Order type: ", this);
	tradeTypeLabel->setGeometry(10, 290, 150, 40);
	tradeTypeEdit = new QComboBox(this);
	QStringList tradeTypes;
	tradeTypes.append("Market");
	tradeTypes.append("Limit");
	tradeTypes.append("Pegged");
	tradeTypeEdit->addItems(tradeTypes);
	tradeTypeEdit->setGeometry(170, 290, 310, 40);

	// Limit for limit orders
	limitLabel = new QLabel("Price Limit: ", this);
	limitLabel->setGeometry(10, 340, 150, 40);
	limitEdit = new QLineEdit(this);
	limitEdit->setGeometry(170, 340, 310, 40);
    limitEdit->setDisabled(true);

	// Expiration date field
	expLabel = new QLabel("Contract expiry: ", this);
	expLabel->setGeometry(10, 390, 460, 40);
	expDate = new QDateEdit(this);
    expDate->setDate(QDate::currentDate());
	expDate->setGeometry(10, 440, 460, 40);
	expDate->setDisplayFormat("M/yyyy");
    // *** END NEW ORDER FORM *** ==============================================

    // *** CURRENT SYMBOL DISPLAY *** ==========================================
    // Contract contract = request_info("CME/CLH2015");

    selectedTitleLabel = new QLabel("Selected Contract:", this);
    selectedTitleLabel->setGeometry(520, 40, 460, 40);
    selectedNameLabel = new QLabel("Name: N/A", this);
    selectedNameLabel->setGeometry(520, 90, 460, 40);
    selectedPriceLabel = new QLabel("Price: N/A", this);
    selectedPriceLabel->setGeometry(520, 140, 460, 40);
    // *** END CURRENT SYMBOL DISPLAY *** ======================================


	// Create and position submit button
	submitButton = new QPushButton("Submit", this);
	submitButton->setGeometry(490, 640, 100, 40);

	// Connect submit button
	connect(submitButton, SIGNAL(clicked()), this, SLOT (slotSubmission()));
}

GUI::~GUI() {
	delete downloadAggregateAct;
	delete downloadAllAct;
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
    delete downloadDetailedPLAct;
    delete downloadPLAct;
    delete selectedNameLabel;
    delete selectedPriceLabel;
    delete selectedTitleLabel;
    delete settingsMenu;
}

void GUI::slotSubmission() {
	// Text fields
	string symbol = symbolEdit->currentText().toStdString();
	string price_string = priceEdit->text().toStdString();
	string qty_string = qtyEdit->text().toStdString();
	string trader = traderEdit->text().toStdString();
	string expiry = expDate->date().toString().toStdString();
	string datetime = QDateTime::currentDateTime().toString().toStdString();

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
		Order tmp(symbol, qty, price, buy, expiry, datetime, trader);
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

void GUI::slotHandleSymbolChange(const QString& text) {
    auto selectedContract = book->get_contract(text.toStdString());
    cout << selectedContract.toString();
    string nameString = "Name: ";
    nameString += selectedContract.get_name();
    selectedNameLabel->setText(nameString.c_str());
    string priceString = "Latest Price: ";
    priceString += to_string(selectedContract.get_last_price());
    selectedPriceLabel->setText(priceString.c_str());
}
