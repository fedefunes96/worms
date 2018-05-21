/********************************************************************************
** Form generated from reading UI file 'editorpantalla.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORPANTALLA_H
#define UI_EDITORPANTALLA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditorPantalla
{
public:
    QPushButton *agregarGusano;
    QLineEdit *vidaGusano;
    QPushButton *AgregarViga;
    QPushButton *SelecionarHerramintas_Armas;
    QPushButton *agregarVigaChica;
    QGraphicsView *graphicsView;
    QPushButton *quitar;
    QPushButton *mas;
    QPushButton *menos;
    QLabel *label;
    QPushButton *saveAs;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *EditorPantalla)
    {
        if (EditorPantalla->objectName().isEmpty())
            EditorPantalla->setObjectName(QStringLiteral("EditorPantalla"));
        EditorPantalla->resize(1622, 799);
        agregarGusano = new QPushButton(EditorPantalla);
        agregarGusano->setObjectName(QStringLiteral("agregarGusano"));
        agregarGusano->setGeometry(QRect(1480, 20, 141, 21));
        vidaGusano = new QLineEdit(EditorPantalla);
        vidaGusano->setObjectName(QStringLiteral("vidaGusano"));
        vidaGusano->setGeometry(QRect(1390, 20, 81, 25));
        vidaGusano->setMaxLength(4);
        vidaGusano->setCursorPosition(4);
        vidaGusano->setClearButtonEnabled(true);
        AgregarViga = new QPushButton(EditorPantalla);
        AgregarViga->setObjectName(QStringLiteral("AgregarViga"));
        AgregarViga->setGeometry(QRect(1442, 60, 151, 25));
        SelecionarHerramintas_Armas = new QPushButton(EditorPantalla);
        SelecionarHerramintas_Armas->setObjectName(QStringLiteral("SelecionarHerramintas_Armas"));
        SelecionarHerramintas_Armas->setGeometry(QRect(1382, 160, 231, 25));
        agregarVigaChica = new QPushButton(EditorPantalla);
        agregarVigaChica->setObjectName(QStringLiteral("agregarVigaChica"));
        agregarVigaChica->setGeometry(QRect(1450, 100, 141, 25));
        graphicsView = new QGraphicsView(EditorPantalla);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 1371, 801));
        quitar = new QPushButton(EditorPantalla);
        quitar->setObjectName(QStringLiteral("quitar"));
        quitar->setGeometry(QRect(1488, 280, 121, 25));
        mas = new QPushButton(EditorPantalla);
        mas->setObjectName(QStringLiteral("mas"));
        mas->setGeometry(QRect(1570, 320, 31, 25));
        menos = new QPushButton(EditorPantalla);
        menos->setObjectName(QStringLiteral("menos"));
        menos->setGeometry(QRect(1568, 350, 31, 25));
        label = new QLabel(EditorPantalla);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1460, 210, 67, 17));
        saveAs = new QPushButton(EditorPantalla);
        saveAs->setObjectName(QStringLiteral("saveAs"));
        saveAs->setGeometry(QRect(1510, 440, 89, 25));
        pushButton = new QPushButton(EditorPantalla);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1510, 480, 89, 25));
        pushButton_2 = new QPushButton(EditorPantalla);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(1510, 520, 89, 25));

        retranslateUi(EditorPantalla);

        QMetaObject::connectSlotsByName(EditorPantalla);
    } // setupUi

    void retranslateUi(QDialog *EditorPantalla)
    {
        EditorPantalla->setWindowTitle(QApplication::translate("EditorPantalla", "Dialog", nullptr));
        agregarGusano->setText(QApplication::translate("EditorPantalla", "Agregar Gusano", nullptr));
        vidaGusano->setText(QApplication::translate("EditorPantalla", "vida", nullptr));
        AgregarViga->setText(QApplication::translate("EditorPantalla", "Agregar Viga Grande", nullptr));
        SelecionarHerramintas_Armas->setText(QApplication::translate("EditorPantalla", "Selecionar Heraminetas/Armas", nullptr));
        agregarVigaChica->setText(QApplication::translate("EditorPantalla", "Agregar Viga chica", nullptr));
        quitar->setText(QApplication::translate("EditorPantalla", "Quitar Elemento", nullptr));
        mas->setText(QApplication::translate("EditorPantalla", "+", nullptr));
        menos->setText(QApplication::translate("EditorPantalla", "-", nullptr));
        label->setText(QApplication::translate("EditorPantalla", "angulo", nullptr));
        saveAs->setText(QApplication::translate("EditorPantalla", "Save as", nullptr));
        pushButton->setText(QApplication::translate("EditorPantalla", "Save", nullptr));
        pushButton_2->setText(QApplication::translate("EditorPantalla", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditorPantalla: public Ui_EditorPantalla {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORPANTALLA_H
