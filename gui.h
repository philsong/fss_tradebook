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

#include <memory>

#include "tradebook.h"

class GUI : public QMainWindow {
    Q_OBJECT

private slots:
	void slotSubmission();
    void slotDownload();

private:
	// GUI Elements
    QAction* downloadAct;
    QMenu* fileMenu;
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
