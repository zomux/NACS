#include <QtGui>
#include <QSettings>
#include "browser.h"
#include "nacs.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }

    QSettings *cfgNACS = new QSettings("config.ini",QSettings::IniFormat,0);
    QString szUrlManager=cfgNACS->value("/NACS/MANAGER","").toString();
    QString szUrlServer=cfgNACS->value("/NACS/SERVER","").toString();

    NACS* app_nacs=new NACS(szUrlServer,szUrlManager);
    app_nacs->publicShowLoginDialog();
   // Browser *browser=new Browser(szUrl);
   // browser->show();

    return a.exec();

}
