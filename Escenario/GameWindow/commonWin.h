#ifndef COMMONWIN_H
#define COMMONWIN_H

#include <QWidget>
#include <QDialog>
#include "backgrounMusic.h"

namespace Ui {
class commonWIn;
}

class commonWIn : public QDialog
{
    Q_OBJECT

public:
    explicit commonWIn(QWidget *parent = nullptr);
    ~commonWIn();

private:
    Ui::commonWIn *ui;
    backgrounMusic *b;
};

#endif // COMMONWIN_H
