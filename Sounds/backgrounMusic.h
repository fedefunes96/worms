#ifndef BACKGROUNMUSIC_H
#define BACKGROUNMUSIC_H

#include <QString>
#include <QMediaPlayer>
#include <QMediaPlaylist>

//Clase que encapsula la musica de fondo
//inicializarlo con new
class backgrounMusic
{
public:
    backgrounMusic();

    //Crea una musica de fondo y empieza el loop,
    //se le deve pasar el path realtivo
    backgrounMusic(const QString &relativePath);

    //detiene la musica
    void stop();

    ~backgrounMusic();

private:
    QMediaPlayer *player;
    QMediaPlaylist *list;
};

#endif // BACKGROUNMUSIC_H
