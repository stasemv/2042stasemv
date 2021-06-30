#include "clsMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    nsp2042::clsMainWindow w;
    w.show();

    return a.exec();
}
