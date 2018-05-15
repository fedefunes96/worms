#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editorpantalla.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    EditorPantalla pantalla2;
    pantalla2.setModal(true);
    pantalla2.exec();
}

