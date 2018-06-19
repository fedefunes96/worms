#ifndef ROOMCREATOR_H
#define ROOMCREATOR_H

#include <QWidget>
#include "protocol.h"
#include "button.h"
#include <QLineEdit>
#include <QDialog>
#include "controler.h"
#include "waitRoom.h"

namespace Ui {
class RoomCreator;
}

class RoomCreator : public QDialog
{
    Q_OBJECT

public:
    RoomCreator(WaitRoom* wait,Protocol* protocol,QWidget *parent = nullptr);
    ~RoomCreator();
    void connectControler(Controler *controler);

    void closeEvent(QCloseEvent *event);
public slots:
    void recvMaps(QList<std::string> list);

private slots:
    void on_pushButton_clicked();

signals:
    void closeGame();

private:
    Ui::RoomCreator *ui;
    Protocol* protocol;
    WaitRoom* wait;
    std::vector<button*> buttons;
    std::vector<QLineEdit*> lines;
    bool closeX;
};

#endif // ROOMCREATOR_H
