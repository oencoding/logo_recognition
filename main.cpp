#include "logo_detect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logo_detect w;
    w.show();

    return a.exec();
}
