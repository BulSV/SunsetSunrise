#include <debug.h>
#include <QApplication>
#include "sunsetrise.h"
#include "GetSunSetRise.h"
#include <QtGui>
//#include <QWindowsStyle>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
//    app.setStyle("windows");

    GetSunSetRise w;
    w.show();
    return app.exec();
}
