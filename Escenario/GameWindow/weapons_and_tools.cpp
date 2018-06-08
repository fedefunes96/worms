#include "weapons_and_tools.h"
#include "ui_weapons_and_tools.h"
#include <QDebug>


Weapons_and_Tools::Weapons_and_Tools(QWidget *parent,Player* player) :
    QDialog(parent),
    ui(new Ui::Weapons_and_Tools),
    player(player)
{
    ui->setupUi(this);
    if(!this->player->canFire(static_cast<int>(WeaponType::AIRMISIL_ID))){
        ui->misil->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::BAZOOKA_ID))){
        ui->bazooka->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::BANANA_ID))){
        ui->banana->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::MORTER_ID))){
        ui->morter->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::BAT_ID))){
        ui->bat->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::DINAMITE_ID))){
        ui->dinamite->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::GRANADE_ID))){
        ui->granade->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::FRAG_GRANADE_ID))){
        ui->fragGranade->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::HOLY_GRANADE_ID))){
        ui->holyGranade->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::TELEPORT_ID))){
        ui->teleport->setEnabled(false);
    }
    if(!this->player->canFire(static_cast<int>(WeaponType::PUNCH_ID))){
        ui->punch->setEnabled(false);
    }

}

Player* Weapons_and_Tools::getPlayer(){
    return this->player;
}

Weapons_and_Tools::~Weapons_and_Tools()
{
    delete ui;
}

void Weapons_and_Tools::on_misil_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::AIRMISIL_ID));
    close();
}

void Weapons_and_Tools::on_bat_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::BAT_ID));
    close();
}

void Weapons_and_Tools::on_banana_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::BANANA_ID));
    close();
}

void Weapons_and_Tools::on_dinamite_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::DINAMITE_ID));
    close();
}

void Weapons_and_Tools::on_fragGranade_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::FRAG_GRANADE_ID));
    close();
}

void Weapons_and_Tools::on_granade_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::GRANADE_ID));
    close();
}

void Weapons_and_Tools::on_holyGranade_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::HOLY_GRANADE_ID));
    close();
}

void Weapons_and_Tools::on_morter_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::MORTER_ID));
    close();
}

void Weapons_and_Tools::on_teleport_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::TELEPORT_ID));
    close();
}

void Weapons_and_Tools::on_bazooka_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::BAZOOKA_ID));
    close();
}

void Weapons_and_Tools::on_punch_clicked()
{
    this->player->getWormActive()->loadSpriteWeapon(static_cast<int>(WeaponType::PUNCH_ID));
    close();
}
