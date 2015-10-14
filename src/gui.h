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

#include <memory>

#include "tradebook.h"

class GUI : public QMainWindow {
    Q_OBJECT

private slots:
    /// Qt Slot for Trade submission.
	void slotSubmission();
    /// Qt Slot for downloading all Trade data.
    void slotDownload();
    /// Qt Slot for downloading aggregate positions.
    void slotAggregateDownload();

private:
	// GUI Elements
    QAction * downloadAct;
    QAction * downloadAggregateAct;
    QMenu * fileMenu;
    QPushButton * submitButton;

    QLabel * symbolLabel;
    QLineEdit * symbolEdit;

    QLabel * priceLabel;
    QLineEdit * priceEdit;

    QLabel * qtyLabel;
    QLineEdit * qtyEdit;

    QLabel * traderLabel;
    QLineEdit * traderEdit;

    QRadioButton * buyButton;
    QRadioButton * sellButton;

    QLabel * expLabel;
    QDateEdit * expDate;

    QLabel * transactionLabel;
    QDateTimeEdit * transactionDateTime;

    /// Link to TradeBook instance associated with GUI
    TradeBook* book;

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
