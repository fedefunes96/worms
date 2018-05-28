#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "backgrounMusic.h"
#include "generalSounds.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //sounds.emplace_back("../Sounds/sounds/English/AMAZING.WAV");
    //sounds.emplace_back("../Sounds/sounds/English/BORING.WAV");
    generalSounds *a = new generalSounds("../Sounds/sounds/English/AMAZING.WAV");
    generalSounds *b = new generalSounds("../Sounds/sounds/English/BORING.WAV");
    sounds.push_back(a);
    sounds.push_back(b);
}

MainWindow::~MainWindow()
{
    for (auto &a : sounds){
        delete a;
        std::cout<<"hola"<<std::endl;
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    sounds[0]->play();
}

void MainWindow::on_pushButton_2_clicked()
{
    sounds[1]->play();
}
