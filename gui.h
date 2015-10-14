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
	void slotSubmission();
    void slotDownload();
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

    // Link to TradeBook
    TradeBook* book;

public:
    GUI(QWidget * parent, TradeBook * tb);
    ~GUI();
    
};

#endif // GUI_H
