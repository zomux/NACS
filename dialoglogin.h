#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <nacs.h>

class NACS;
namespace Ui {
    class DialogLogin;
}

class DialogLogin : public QDialog {
    Q_OBJECT
public:
    DialogLogin(NACS* nacs);
    ~DialogLogin();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogLogin *ui;
    NACS* m_nacs;

private slots:
    void on_BtnCancel_clicked();
    void on_BtnLogin_clicked();
};

#endif // DIALOGLOGIN_H
