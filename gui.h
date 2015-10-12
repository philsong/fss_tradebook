#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QApplication>

class GUI : public QMainWindow {
    Q_OBJECT

private:
    QPushButton* submitButton;

public:
    GUI(QWidget *parent = 0);
    ~GUI();
    
};

#endif // GUI_H
