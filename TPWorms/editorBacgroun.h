#ifndef EDITORBACGROUN_H
#define EDITORBACGROUN_H

#include <QWidget>

namespace Ui {
class editorBacgroun;
}

class editorBacgroun : public QWidget
{
    Q_OBJECT

public:
    explicit editorBacgroun(QWidget *parent = 0);
    ~editorBacgroun();

private:
    Ui::editorBacgroun *ui;
};

#endif // EDITORBACGROUN_H
