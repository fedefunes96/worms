#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QDialog>
#include <map>
#include <QtCore>
#include <QtGui>
#include "editorusables.h"
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QString>
#include "editorworm.h"
#include "editorviga.h"
#include "celda.h"
#include <QDropEvent>
#include <vector>

namespace Ui {
class editor;
}

class editor : public QDialog
{
    Q_OBJECT

public:
    explicit editor(QWidget *parent = nullptr);
    ~editor();

private:
    Ui::editor *ui;
    QGraphicsScene * scene;
    int xscene;
    int yscene;
    //celda celdas[600][500];
};

#endif
