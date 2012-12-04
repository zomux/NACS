#include "dialoglogin.h"
#include "ui_dialoglogin.h"

DialogLogin::DialogLogin(NACS* nacs) :
    QDialog(),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

    m_nacs=nacs;
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogLogin::on_BtnLogin_clicked()
{
    m_nacs->userLogin( ui->txtUsername->text() , ui->txtPassword->text() );
    this->close();
}

void DialogLogin::on_BtnCancel_clicked()
{
    this->close();
}
