#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>

#include "camera.h"
#include "game_view.h"
#include "weapons_and_tools.h"
#include "player.h"

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
private slots:
    void on_pushButton_clicked();

private:
    Ui::GameWindow *ui;
    Game_View *gameScene;
    Weapons_and_Tools *menuWeapons;
    Player *playerActive;
};

#endif // GAMEWINDOW_H
