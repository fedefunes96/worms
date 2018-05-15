#ifndef EDITORPANTALLA_H
#define EDITORPANTALLA_H

#include <QDialog>

namespace Ui {
class EditorPantalla;
}

class EditorPantalla : public QDialog
{
    Q_OBJECT

public:
    explicit EditorPantalla(QWidget *parent = 0);
    ~EditorPantalla();

private slots:
    void on_buttonBox_accepted();

    void on_agregarGusano_clicked();

    void on_AgregarViga_clicked();

    void on_SelecionarHerramintas_Armas_clicked();

private:
    Ui::EditorPantalla *ui;
};

#endif // EDITORPANTALLA_H
