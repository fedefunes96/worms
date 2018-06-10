#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
#include "protocol.h"

namespace Ui {
class clientMainWindow;
}

class clientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientMainWindow(QWidget *parent = 0);
    ~clientMainWindow();

private slots:
    void on_mapSelection_clicked();

    void on_pushButton_clicked();

private:
    Ui::clientMainWindow *ui;
};

#endif
