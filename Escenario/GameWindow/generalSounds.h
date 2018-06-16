#ifndef GENERALSOUNDS_H
#define GENERALSOUNDS_H

#include <QString>
#include <QMediaPlayer>
#include <QMediaPlaylist>

//Clase que encapsula los sonidos para usos generales
//inicializar con new
class generalSounds
{
public:
    generalSounds();

    //inicializador de sonidos, se le deve pasar el path realtivo
    generalSounds(const QString &relativePath);

    ~generalSounds();

    //empieza el sonido
    void play();

private:
    QMediaPlayer *player;
};

#endif // GENERALSOUNDS_H
