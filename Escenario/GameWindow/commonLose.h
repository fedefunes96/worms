#ifndef COMMONLOSE_H
#define COMMONLOSE_H

#include <QWidget>
#include "backgrounMusic.h"

namespace Ui {
class commonLose;
}

class commonLose : public QWidget
{
    Q_OBJECT

public:
    explicit commonLose(QWidget *parent = 0);
    ~commonLose();

private:
    Ui::commonLose *ui;
    backgrounMusic *b;
};

#endif // COMMONLOSE_H
