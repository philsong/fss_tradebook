#ifndef GUI_H
#define GUI_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "tradebook.h"

class GUI : public QMainWindow {
    Q_OBJECT

private slots:
	void slotSubmission();

private:
	// GUI Elements
    QPushButton* submitButton;
    QLabel* symbolLabel;
    QLineEdit* symbolEdit;
    QLabel* priceLabel;
    QLineEdit* priceEdit;
    QLabel* qtyLabel;
    QLineEdit* qtyEdit;

    // Link to TradeBook
    TradeBook* book;

public:
    GUI(QWidget *parent, TradeBook * tb);
    ~GUI();
    
};

#endif // GUI_H
