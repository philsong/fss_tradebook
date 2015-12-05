/**
 * \class GUI
 *
 * \brief Implementation of Graphical User Interface.
 *
 * This class extends Qt's QMainWindow with
 * a selection of widgets that implement the
 * trade submission form.
 */

#ifndef GUI_H
#define GUI_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QRadioButton>
#include <QDateTimeEdit>

#include <QComboBox>
#include <QStringList>

#include <memory>

#include "tradebook.hpp"
#include "contract.hpp"

class GUI : public QMainWindow {
    Q_OBJECT

private slots:
    /// Qt Slot for Trade submission.
	void slotSubmission();
    /// Qt Slot for downloading all Trade data.
    void slotDownload();
    /// Qt Slot for downloading aggregate positions.
    void slotAggregateDownload();

    void slotHandleSymbolChange(const QString& text);

private:

	// GUI Elements
    QPushButton * submitButton;

    // ==
    QMenu * fileMenu;
    QAction * downloadAct;
    QAction * downloadAggregateAct;

    QMenu * settingsMenu;
    // ==

    // ==
    QLabel * symbolLabel;
    QComboBox * symbolEdit;

    QLabel * priceLabel;
    QLineEdit * priceEdit; // Now defined according to symbol

    QLabel * qtyLabel;
    QLineEdit * qtyEdit;

    QLabel * traderLabel;
    QLineEdit * traderEdit; // ok

    QLabel * tradeTypeLabel;
    QComboBox * tradeTypeEdit; // QDropDown for market, limit, or pegged

    QRadioButton * buyButton;
    QRadioButton * sellButton;

    // Price limit for limit order
    QLabel * limitLabel;
    QLineEdit * limitEdit;

    QLabel * expLabel;
    QDateEdit * expDate;

    QLabel * transactionLabel;
    QDateTimeEdit * transactionDateTime;
    // ==

    // ==
    QLabel * selectedTitleLabel;
    QLabel * selectedNameLabel;
    QLabel * selectedPriceLabel;
    // ==

    /// Link to TradeBook instance associated with GUI
    TradeBook* book;

    /// List of Symbols available for orders
    QStringList symbols;

public:
   /**
    * Constructor for the GUI.
    * Attaches the QMainWindow parent to the QApplication
    * and TradeBook instance.
    * \param tb TradeBook instance attached to the GUI
    */
    GUI(QWidget * parent, TradeBook * tb);
    ~GUI();

};

#endif // GUI_H
