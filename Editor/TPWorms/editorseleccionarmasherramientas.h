#ifndef EDITORSELECCIONARMASHERRAMIENTAS_H
#define EDITORSELECCIONARMASHERRAMIENTAS_H

#include <QDialog>

namespace Ui {
class editorSeleccionArmasHerramientas;
}

class editorSeleccionArmasHerramientas : public QDialog
{
    Q_OBJECT

public:
    explicit editorSeleccionArmasHerramientas(QWidget *parent = 0);
    ~editorSeleccionArmasHerramientas();

private:
    Ui::editorSeleccionArmasHerramientas *ui;
};

#endif // EDITORSELECCIONARMASHERRAMIENTAS_H
