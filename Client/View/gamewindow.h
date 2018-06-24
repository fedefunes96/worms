#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>

#include "camera.h"
#include "stage.h"
#include "weapons_and_tools.h"
#include "player.h"
#include <QTimer>
#include <QApplication>


namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QApplication *app,QWidget *parent = 0);
    ~GameWindow();

    void addPlayer(Player *player);
    void addGameScene(Stage *gameScene);
    Camera *getCamera();
    void setButtonEnable(bool enable);
    void setBar(int pot);
    void startTimerRound(int time);
    void setWindParm(int min, int max);
    void setWind(int speed);
    void setRefocusEnable(bool enable);
    void closeEvent(QCloseEvent *event);
    void showPlayerList(QList<Player *> playerList);
    void showActualPlayer(int id);

    void setWinner(bool haswinner);
    void cleanWeaponInfoView();
private slots:
    void on_pushButton_clicked();

    void refreshBox();
    void stepTimer();
    void on_refocus_clicked();

    void on_downCamera_clicked();

    void on_leftCamera_clicked();

    void on_upCamera_clicked();

    void on_rightCamera_clicked();

    void on_time1_clicked();

    void on_time2_clicked();

    void on_time3_clicked();

    void on_time4_clicked();

    void on_time5_clicked();

private:
    void setButtomsCountDownHidden(bool enable);
    void setPowerBarHidden(bool enable);
    Ui::GameWindow *ui;
    Stage *gameScene;
    Weapons_and_Tools *menuWeapons;
    Player *playerActive;
    QTimer *timer;
    QTimer *timerRound;
    int time;
    int timeToReach;
    void setButtomsTime(int time);
    void setButtonTime(QPushButton *button, bool enable);
    QApplication *app;
    bool hasWinner;
};

#endif // GAMEWINDOW_H
