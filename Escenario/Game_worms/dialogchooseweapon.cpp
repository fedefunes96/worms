#include "dialogchooseweapon.h"
#include "ui_dialogchooseweapon.h"

#include <QDebug>

DialogChooseWeapon::DialogChooseWeapon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChooseWeapon)
{
    ui->setupUi(this);
}

DialogChooseWeapon::~DialogChooseWeapon()
{
    delete ui;
}

void DialogChooseWeapon::on_pushButton_clicked()
{

}
