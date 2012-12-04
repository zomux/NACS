#ifndef BROWSER_H
#define BROWSER_H

#include "nacs.h"
#include "nacsif.h"
#include <QtNetwork>
#include <QtGui>

class NACSIF;
class NACS;
class QWebView;
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
//! [1]
class Browser : public QMainWindow
{
    Q_OBJECT

public:
    Browser(NACS* nacs,QString szUrl);

protected slots:

    void adjustLocation();
    void changeLocation();
    void adjustTitle();
    void setProgress(int p);
    void finishLoading();
    void keyPressEvent(QKeyEvent *k);
private:
    QWebView *view;
    QLineEdit *locationEdit;
    QToolBar *toolBar;

    NACSIF* m_nacsif;
    NACS* m_nacs;
    int progress;
//! [1]
};
#endif // BROWSER_H
