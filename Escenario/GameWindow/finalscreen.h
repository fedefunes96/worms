#ifndef FINALSCREEN_H
#define FINALSCREEN_H

#include <QDialog>
#include "gameclass.h"
#include <QApplication>
#include "backgrounMusic.h"

namespace Ui {
class FinalScreen;
}

class FinalScreen : public QDialog
{
    Q_OBJECT

public:
    FinalScreen(QApplication *app,QWidget *parent = 0);
    ~FinalScreen();

    void connectGame(GameClass *game);
    void closeEvent(QCloseEvent *event);
public slots:
    void setIsWinner(bool iswinner);
private:
    void setWinner();
    void setLoser();
    Ui::FinalScreen *ui;
    QApplication *app;
    backgrounMusic* b;
};

#endif // FINALSCREEN_H
