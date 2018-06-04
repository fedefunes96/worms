#ifndef COMMONWIN_H
#define COMMONWIN_H

#include <QWidget>

namespace Ui {
class commonWIn;
}

class commonWIn : public QWidget
{
    Q_OBJECT

public:
    explicit commonWIn(QWidget *parent = 0);
    ~commonWIn();

private:
    Ui::commonWIn *ui;
};

#endif // COMMONWIN_H
