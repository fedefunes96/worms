#ifndef COMMONLOSE_H
#define COMMONLOSE_H

#include <QWidget>

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
};

#endif // COMMONLOSE_H
