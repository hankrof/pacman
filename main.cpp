#include "view/pcmainwindow.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PcMainWindow w;
    w.show();
    return a.exec();
}
