#include "gui.h"
#include "database.h"

int main(int argc, char *argv[])
{	
	Database db("tradeBookDB", 5432);

    QApplication app(argc, argv);
    GUI w;
    w.show();

    return app.exec();
}
