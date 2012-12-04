#ifndef NACS_H
#define NACS_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QtGui>
#include <QHttp>
#include <QFile>
#include <QCryptographicHash>
#include <QSettings>
 #include <QFileDialog>
 #include <QTimer>
#include <dialoglogin.h>
#include "browser.h"
#include "nacs_func.h"
#include "shlobj.h"
#include "insrdrv.h"

#define NACS_WEB_SK "w9+vW-j93p"
#define NACS_REG_PATH "HKEY_LOCAL_MACHINE\\Software\\NacsValidPids"


QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class DialogLogin;
class Browser;
QT_END_NAMESPACE

class NACS : public QObject
{
    Q_OBJECT

public:
    /* def for functions */
    NACS(QString urlServer,QString urlManager);
    void showMessage(QString szMessage);
    void userLogin(QString szUsername,QString szPassword);
    void userLogout();
    void userMountAll();
    void userDismountAll();

    void ftpServiceStart();
    void ftpServiceStop();
    void ftpCreateAccounts();
    bool ftpExists();

    bool mount(QString szSourceVol,QString szName,QString szDestVol,QString szAccess);
    bool dismount(QString szDestVol);
    bool format(QString szVol,QString Name,long nSize);
    bool callBase(QString szArg);
    QString productBaseKey();

    QStringList getAllFreeDrivers();
    QString getFreeDriver();
    QString md5(QString str,bool bFuck=false);
    bool createDesktopShotCut(QString);
    bool loadMonDriver();
    DWORD productDriveWord();
    /* definations for var */
    bool isMonLoaded;
    HANDLE hDevice;
    FILTER FilterDefinition;

    QSystemTrayIcon *trayIcon;
    QString urlServer;
    QString urlManager;

    QMenu* menuTray;
    QAction* actionLogin;
    QAction* actionManage;
    QAction* actionValidProcess;
    QAction* actionRunValid;
    QAction* actionExit;

    QString userName;
    QString userPass;
    QStringList userAccess;
    QStringList userPrivilege;
    QMap<QString,QString> mapMountedDrivers;
    bool userLogged;
    bool userOwner;

    QHttp* httpServer;

    QTimer* timerRefresh;

    DialogLogin* dlgLogin;
    Browser* dlgBrowser;
    void publicShowLoginDialog();

private slots:
    void refreshOnline();
    void callbackUserLogin(bool bSuccess);
    void showLoginDialog();
    void showManager();
    void iconActived(QSystemTrayIcon::ActivationReason reason);
    void quitApp();
    void triggleValidProcess(bool);
    void toggleRunValid();
    void callExplorer(QString szAddress);
};

#endif // NACS_H
