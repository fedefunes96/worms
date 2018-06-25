#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	//Accion del boton NewMap
    void on_pushButton_clicked();

    //Accion del boton LoadMap
    void on_load_clicked();

private:
    Ui::MainWindow *ui;
};

#endif 
