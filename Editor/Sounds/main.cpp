#include "mainwindow.h"
#include <QApplication>
#include "commonWin.h"
#include "commonLose.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    commonLose w;
    w.show();

    return a.exec();
}
