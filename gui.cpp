#include "gui.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent) {
	setFixedSize(600, 400);
	setWindowTitle("FSS TradeBook");
}

GUI::~GUI() {

}
