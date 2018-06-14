#include "mainwindow.h"
#include <QApplication>
#include "commonparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    commonParser::saveConfig();
    MainWindow w;
    w.show();
    return a.exec();
}
