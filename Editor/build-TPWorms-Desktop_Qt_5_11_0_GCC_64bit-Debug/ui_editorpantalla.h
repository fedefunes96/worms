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
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditorPantalla
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *agregarGusano;
    QLineEdit *vidaGusano;
    QPushButton *AgregarViga;
    QPushButton *SelecionarHerramintas_Armas;
    QLineEdit *vigaAngulo;
    QLineEdit *yViga;
    QLineEdit *yGusano;
    QLineEdit *xGusano;
    QLineEdit *xViga;

    void setupUi(QDialog *EditorPantalla)
    {
        if (EditorPantalla->objectName().isEmpty())
            EditorPantalla->setObjectName(QStringLiteral("EditorPantalla"));
        EditorPantalla->resize(1037, 324);
        buttonBox = new QDialogButtonBox(EditorPantalla);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(660, 210, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        agregarGusano = new QPushButton(EditorPantalla);
        agregarGusano->setObjectName(QStringLiteral("agregarGusano"));
        agregarGusano->setGeometry(QRect(860, 60, 141, 21));
        vidaGusano = new QLineEdit(EditorPantalla);
        vidaGusano->setObjectName(QStringLiteral("vidaGusano"));
        vidaGusano->setGeometry(QRect(770, 60, 81, 25));
        vidaGusano->setMaxLength(4);
        vidaGusano->setCursorPosition(4);
        vidaGusano->setClearButtonEnabled(false);
        AgregarViga = new QPushButton(EditorPantalla);
        AgregarViga->setObjectName(QStringLiteral("AgregarViga"));
        AgregarViga->setGeometry(QRect(860, 100, 141, 25));
        SelecionarHerramintas_Armas = new QPushButton(EditorPantalla);
        SelecionarHerramintas_Armas->setObjectName(QStringLiteral("SelecionarHerramintas_Armas"));
        SelecionarHerramintas_Armas->setGeometry(QRect(768, 150, 231, 25));
        vigaAngulo = new QLineEdit(EditorPantalla);
        vigaAngulo->setObjectName(QStringLiteral("vigaAngulo"));
        vigaAngulo->setGeometry(QRect(770, 100, 81, 25));
        vigaAngulo->setMaxLength(6);
        vigaAngulo->setClearButtonEnabled(false);
        yViga = new QLineEdit(EditorPantalla);
        yViga->setObjectName(QStringLiteral("yViga"));
        yViga->setGeometry(QRect(722, 100, 41, 25));
        yViga->setMaxLength(3);
        yViga->setClearButtonEnabled(false);
        yGusano = new QLineEdit(EditorPantalla);
        yGusano->setObjectName(QStringLiteral("yGusano"));
        yGusano->setGeometry(QRect(722, 60, 41, 25));
        yGusano->setMaxLength(3);
        yGusano->setClearButtonEnabled(false);
        xGusano = new QLineEdit(EditorPantalla);
        xGusano->setObjectName(QStringLiteral("xGusano"));
        xGusano->setGeometry(QRect(672, 60, 41, 25));
        xGusano->setMaxLength(3);
        xGusano->setClearButtonEnabled(false);
        xViga = new QLineEdit(EditorPantalla);
        xViga->setObjectName(QStringLiteral("xViga"));
        xViga->setGeometry(QRect(672, 100, 41, 25));
        xViga->setMaxLength(3);
        xViga->setClearButtonEnabled(false);

        retranslateUi(EditorPantalla);
        QObject::connect(buttonBox, SIGNAL(rejected()), EditorPantalla, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), EditorPantalla, SLOT(accept()));

        QMetaObject::connectSlotsByName(EditorPantalla);
    } // setupUi

    void retranslateUi(QDialog *EditorPantalla)
    {
        EditorPantalla->setWindowTitle(QApplication::translate("EditorPantalla", "Dialog", nullptr));
        agregarGusano->setText(QApplication::translate("EditorPantalla", "Agregar Gusano", nullptr));
        vidaGusano->setText(QApplication::translate("EditorPantalla", "vida", nullptr));
        AgregarViga->setText(QApplication::translate("EditorPantalla", "AgregarViga", nullptr));
        SelecionarHerramintas_Armas->setText(QApplication::translate("EditorPantalla", "Selecionar Heraminetas/Armas", nullptr));
        vigaAngulo->setText(QApplication::translate("EditorPantalla", "angulo", nullptr));
        yViga->setText(QApplication::translate("EditorPantalla", "Y", nullptr));
        yGusano->setText(QApplication::translate("EditorPantalla", "Y", nullptr));
        xGusano->setText(QApplication::translate("EditorPantalla", "x", nullptr));
        xViga->setText(QApplication::translate("EditorPantalla", "x", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditorPantalla: public Ui_EditorPantalla {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORPANTALLA_H
