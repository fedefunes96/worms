#ifndef WAITROOM_H
#define WAITROOM_H

#include <QWidget>

namespace Ui {
class WaitRoom;
}

class WaitRoom : public QWidget
{
    Q_OBJECT

public:
    explicit WaitRoom(QWidget *parent = nullptr);
    ~WaitRoom();

private:
    Ui::WaitRoom *ui;
};

#endif // WAITROOM_H
