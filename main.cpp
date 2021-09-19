#include <QApplication>

#include "GetSunSetRise.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    GetSunSetRise w;
    w.show();

    return app.exec();
}
