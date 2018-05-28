#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editorpantalla.h"
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Editor de mapas");
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


void MainWindow::on_load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open"),
                                                    tr("Escenario *.cfg"));
    if (fileName.isEmpty()){
        return;
    }
    EditorPantalla pantalla2;
    pantalla2.setModal(true);
    pantalla2.fileName(fileName);
    pantalla2.exec();
}
