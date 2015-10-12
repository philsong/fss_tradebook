#ifndef GUI_H
#define GUI_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class GUI : public QMainWindow {
    Q_OBJECT

private slots:
	void submitButtonClicked();

private:
    QPushButton* submitButton;
    QLabel* symbolLabel;
    QLineEdit* symbolEdit;
    QLabel* priceLabel;
    QLineEdit* priceEdit;

public:
    GUI(QWidget *parent = 0);
    ~GUI();
    
};

#endif // GUI_H
