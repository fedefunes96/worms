#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>

#include "camera.h"
#include "game_view.h"
#include "weapons_and_tools.h"
#include "player.h"
#include <QTimer>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    void addPlayer(Player *player);
    void addGameScene(Game_View *gameScene);
    Camera *getCamera();
    void setButtonEnable(bool enable);
    void setBar(int pot);
    void startTimerRound(int time);
    void setWindParm(int min, int max);
    void setWind(int speed);
    void setRefocusEnable(bool enable);
    void closeEvent(QCloseEvent *event);
    void showPlayerList(QList<Player *> playerList);
signals:
    void closeGame();
private slots:
    void on_pushButton_clicked();

    void refreshBox();
    void stepTimer();
    void on_refocus_clicked();

    void on_downCamera_clicked();

    void on_leftCamera_clicked();

    void on_upCamera_clicked();

    void on_rightCamera_clicked();

private:
    Ui::GameWindow *ui;
    Game_View *gameScene;
    Weapons_and_Tools *menuWeapons;
    Player *playerActive;
    QTimer *timer;
    QTimer *timerRound;
    int time;
    int timeToReach;
};

#endif // GAMEWINDOW_H
