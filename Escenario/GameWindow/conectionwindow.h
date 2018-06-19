#ifndef CONECTIONWINDOW_H
#define CONECTIONWINDOW_H

#include <QDialog>
#include "socket.h"
#include "common_socket_exception.h"
#include <vector>

namespace Ui {
class ConectionWindow;
}

class ConectionWindow : public QDialog
{
    Q_OBJECT

public:
    ConectionWindow(QWidget *parent = 0);
    ~ConectionWindow();

    Socket getSocket();
    bool closeWithX();
private slots:
    void on_pushButton_clicked();

private:
    Ui::ConectionWindow *ui;
    std::vector<Socket> list;
    bool closeX;
};

#endif // CONECTIONWINDOW_H
