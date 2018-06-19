#include "generalSounds.h"
#include <QFileInfo>
#include <QDebug>

generalSounds::generalSounds()
{

}

generalSounds::generalSounds(const QString &relativePath)
{
    this->player = new QMediaPlayer();
    player->setMedia(QUrl::fromUserInput(ROOT_PATH+relativePath));
}

generalSounds::~generalSounds()
{
    player->stop();
    delete player;
}

void generalSounds::play()
{
    player->play();
    //qDebug() << player->errorString();
}
