#include "editor_view.h"
#include <QMouseEvent>
#include "editor_viga_view.h"
#include "editor_worm_view.h"
#include <QMessageBox>

editor_view::editor_view()
{

}

void editor_view::mousePressEvent(QMouseEvent *event)
{

    int x = event->x();
    int y = event->y();
    if (this->estado == 1){
        this->agregar_gusano(x,y);
    }

    if (this->estado == 2){
        this->agregar_viga_grande(x,y);
    }

    if (this->estado == 3){
        agregar_viga_chica(x,y);
    }
    //ui->label->setText(QString::number(x));
    //ui->label_2->setText(QString::number(y));
}

void editor_view::agregar_gusano(int x, int y)
{
    int celdaX = x/50;
    int celdaY = y/50;
    x = celdaX*50;
    y = celdaY*50;
    int piso = x +25;
    int altura = y +1;
    if (!celdas[celdaX][celdaY].esta_ocupado()){
        //int vida = ui->vidaGusano->text().toInt();
        if (true){
            QGraphicsItem *worm = new Worm_View();
            scene->addItem(worm);
            worm->setPos(x,y);
            celdas[celdaX][celdaY].llenar_celda(id);
            /*this->worms.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(id++),
                                       std::forward_as_tuple(piso,altura,vida));*/
            this->estado = 0;
        } else {
            QMessageBox::information(this, tr("Error"), tr("vida invalida"));
        }
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada"));
    }
}

void editor_view::agregar_viga_grande(int x, int y)
{
    int celdaX = x/50;
    int celdaY = y/50;
    bool ocupadas = celdas[celdaX][celdaY].esta_ocupado() ||
            celdas[celdaX-1][celdaY].esta_ocupado() || celdas[celdaX-2][celdaY].esta_ocupado()
            || celdas[celdaX+1][celdaY].esta_ocupado() || celdas[celdaX+2][celdaY].esta_ocupado()
            || celdas[celdaX+3][celdaY].esta_ocupado();
    if (!ocupadas){
        int xn = (celdaX -2)*50;
        int yn = celdaY*50;
        editor_viga_view * viga = new editor_viga_view();
        viga->esGrande(true);
        scene->addItem((QGraphicsItem *)viga);
        viga->setPos(xn,yn);
        celdas[celdaX][celdaY].llenar_celda(id);
        celdas[celdaX-1][celdaY].llenar_celda(id);
        celdas[celdaX-2][celdaY].llenar_celda(id);
        celdas[celdaX+1][celdaY].llenar_celda(id);
        celdas[celdaX+2][celdaY].llenar_celda(id);
        celdas[celdaX+3][celdaY].llenar_celda(id);
        /*this->vigas.emplace(std::piecewise_construct,
                        std::forward_as_tuple(id++),
                        std::forward_as_tuple(x,y));*/
        this->estado = 0;
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada"));
    }
}

void editor_view::agregar_viga_chica(int x, int y)
{
    int celdaX = x/50;
    int celdaY = y/50;
    bool ocupadas = celdas[celdaX][celdaY].esta_ocupado() ||
            celdas[celdaX-1][celdaY].esta_ocupado() || celdas[celdaX+1][celdaY].esta_ocupado();
    if (!ocupadas){
        int xn = (celdaX -1)*50;
        int yn = celdaY*50;
        editor_viga_view * viga = new editor_viga_view();
        viga->esGrande(false);
        scene->addItem((QGraphicsItem*)viga);
        viga->setPos(xn,yn);
        celdas[celdaX][celdaY].llenar_celda(id);
        celdas[celdaX-1][celdaY].llenar_celda(id);
        celdas[celdaX+1][celdaY].llenar_celda(id);
        /*this->vigas.emplace(std::piecewise_construct,
                        std::forward_as_tuple(id++),
                        std::forward_as_tuple(x,y));*/

        this->estado = 0;
    } else {
        QMessageBox::information(this, tr("Error"), tr("celda ocupada"));
    }
}

void editor_view::pasar_esena(QGraphicsScene *escena)
{
    this->scene = escena;
}
