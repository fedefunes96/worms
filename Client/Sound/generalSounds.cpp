#include "generalSounds.h"
#include <QFileInfo>
#include <QDebug>

generalSounds::generalSounds()
{

}

generalSounds::generalSounds(const QString &relativePath)
{
    this->player = new QMediaPlayer();
    player->setMedia(QUrl::fromUserInput(QFileInfo(relativePath).absoluteFilePath()));
}

generalSounds::~generalSounds()
{
    player->stop();
    delete player;
}

void generalSounds::play()
{
	player->setVolume(50);
    player->play();
    //qDebug() << player->errorString();
}
