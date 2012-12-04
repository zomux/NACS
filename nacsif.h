#ifndef NACSIF_H
#define NACSIF_H


#include <QObject>
#include <QtGui>
#include <QCryptographicHash>
#include <QHttp>

#include "browser.h"
#include "nacs_func.h"
#include "nacs.h"
class Browser;
class NACS;
//! [1]
class NACSIF : public QObject
{
    Q_OBJECT

public:
    NACSIF(Browser* pBrowser );
    QString productBaseKey();
    NACS* m_nacs;
    bool callBase(QString szArg);
protected slots:
    QVariant command(QString szCommand,QVariant param);
    bool mount(QString szSourceVol,QString szName,QString szDestVol);
    bool dismount(QString szDestVol);
    bool format(QString szVol,QString Name,long nSize);
    bool deleteFormat(QString szName,QString szVol);
    QString getDiskSerial();
    QString hash(QString str);
    void callExplorer(QString szAddress);
private:
    QHttp* http;
    Browser* m_browser;
    QString urlServer;
//! [1]
};

#endif // NACSIF_H
