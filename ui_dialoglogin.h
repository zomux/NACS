/********************************************************************************
** Form generated from reading UI file 'dialoglogin.ui'
**
** Created: Sat 15. May 18:51:36 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOGIN_H
#define UI_DIALOGLOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogLogin
{
public:
    QLabel *label;
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
    QLabel *label_2;
    QPushButton *BtnLogin;
    QPushButton *BtnCancel;
    QLabel *label_3;

    void setupUi(QDialog *DialogLogin)
    {
        if (DialogLogin->objectName().isEmpty())
            DialogLogin->setObjectName(QString::fromUtf8("DialogLogin"));
        DialogLogin->resize(294, 107);
        label = new QLabel(DialogLogin);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 101, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Black"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        txtUsername = new QLineEdit(DialogLogin);
        txtUsername->setObjectName(QString::fromUtf8("txtUsername"));
        txtUsername->setGeometry(QRect(120, 10, 161, 20));
        txtPassword = new QLineEdit(DialogLogin);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setGeometry(QRect(120, 40, 161, 20));
        txtPassword->setEchoMode(QLineEdit::Password);
        label_2 = new QLabel(DialogLogin);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 40, 101, 16));
        label_2->setFont(font);
        BtnLogin = new QPushButton(DialogLogin);
        BtnLogin->setObjectName(QString::fromUtf8("BtnLogin"));
        BtnLogin->setGeometry(QRect(60, 70, 75, 23));
        BtnLogin->setDefault(true);
        BtnCancel = new QPushButton(DialogLogin);
        BtnCancel->setObjectName(QString::fromUtf8("BtnCancel"));
        BtnCancel->setGeometry(QRect(150, 70, 75, 23));
        label_3 = new QLabel(DialogLogin);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 90, 161, 20));
        label_3->setStyleSheet(QString::fromUtf8("color:#666666;"));

        retranslateUi(DialogLogin);

        QMetaObject::connectSlotsByName(DialogLogin);
    } // setupUi

    void retranslateUi(QDialog *DialogLogin)
    {
        DialogLogin->setWindowTitle(QApplication::translate("DialogLogin", "NACS Login", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogLogin", "Username:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogLogin", "Password:", 0, QApplication::UnicodeUTF8));
        BtnLogin->setText(QApplication::translate("DialogLogin", "Login", 0, QApplication::UnicodeUTF8));
        BtnCancel->setText(QApplication::translate("DialogLogin", "Cancel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DialogLogin", "Register in Account Manager", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogLogin: public Ui_DialogLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOGIN_H
