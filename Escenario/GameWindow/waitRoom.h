#ifndef WAITROOM_H
#define WAITROOM_H

#include <QWidget>
#include "controler.h"

namespace Ui {
class WaitRoom;
}

class WaitRoom : public QWidget
{
    Q_OBJECT

public:
    explicit WaitRoom(QWidget *parent = nullptr);
    ~WaitRoom();

    void connectControler(Controler *controler);
public slots:
    void plysInRoom(int cant);
    void startGameView();

private:
    Ui::WaitRoom *ui;
};

#endif // WAITROOM_H
