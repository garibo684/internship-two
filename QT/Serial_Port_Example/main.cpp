#include "serialport.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Widget sp;
    sp.show();
    return app.exec();
}
