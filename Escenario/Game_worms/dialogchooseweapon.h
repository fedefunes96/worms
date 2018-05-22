#ifndef DIALOGCHOOSEWEAPON_H
#define DIALOGCHOOSEWEAPON_H

#include <QDialog>

namespace Ui {
class DialogChooseWeapon;
}

class DialogChooseWeapon : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseWeapon(QWidget *parent = 0);
    ~DialogChooseWeapon();

private slots:
    void on_label_linkActivated(const QString &link);

    void on_pushButton_clicked();

private:
    Ui::DialogChooseWeapon *ui;
};

#endif // DIALOGCHOOSEWEAPON_H
