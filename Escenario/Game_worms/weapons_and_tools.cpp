#include "weapons_and_tools.h"
#include "ui_weapons_and_tools.h"
#include "worm_view.h"

Weapons_and_Tools::Weapons_and_Tools(QWidget *parent,Worm_View* worm) :
    QDialog(parent),
    ui(new Ui::Weapons_and_Tools),
    worm(worm)
{
    ui->setupUi(this);
}


Weapons_and_Tools::~Weapons_and_Tools()
{
    delete ui;
}

void Weapons_and_Tools::on_misil_clicked()
{
    this->worm->loadSpriteWeapon(0);
    close();
}

void Weapons_and_Tools::on_bat_clicked()
{
    this->worm->loadSpriteWeapon(1);
    close();
}

void Weapons_and_Tools::on_banana_clicked()
{
    this->worm->loadSpriteWeapon(2);
    close();
}

void Weapons_and_Tools::on_dinamite_clicked()
{
    this->worm->loadSpriteWeapon(3);
    close();
}

void Weapons_and_Tools::on_fragGranade_clicked()
{
    this->worm->loadSpriteWeapon(4);
    close();
}

void Weapons_and_Tools::on_granade_clicked()
{
    this->worm->loadSpriteWeapon(5);
    close();
}

void Weapons_and_Tools::on_holyGranade_clicked()
{
    this->worm->loadSpriteWeapon(6);
    close();
}

void Weapons_and_Tools::on_morter_clicked()
{
    this->worm->loadSpriteWeapon(7);
    close();
}

void Weapons_and_Tools::on_teleport_clicked()
{
    this->worm->loadSpriteWeapon(8);
    close();
}

void Weapons_and_Tools::on_bazooka_clicked()
{
    this->worm->loadSpriteWeapon(9);
    close();
}

void Weapons_and_Tools::on_punch_clicked()
{
    this->worm->loadSpriteWeapon(10);
    close();
}
