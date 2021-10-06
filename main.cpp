#include <QApplication>

#include "GetSunsetRise.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    GetSunsetRise w;
    w.show();

    return app.exec();
}
