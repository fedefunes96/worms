#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapeditor.h"
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Map editor");
    QPixmap bkg(ROOT_PATH"/resources/images/backGround.jpeg");
    bkg = bkg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background,bkg);
    palette.setColor(ui->label->foregroundRole(),Qt::green);
    this->setPalette(palette);
    QSize size(500,350);
    this->setMaximumSize(size);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    MapEditor pantalla2;
    pantalla2.setModal(true);
    pantalla2.exec();
}


void MainWindow::on_load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open"),ROOT_PATH"/resources/maps",
                                                    tr("*.yaml"));
    if (fileName.isEmpty()){
        return;
    }
    MapEditor pantalla2;
    pantalla2.setModal(true);
    pantalla2.fileName(fileName);
    pantalla2.exec();
}
