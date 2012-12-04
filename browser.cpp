#include "browser.h"
#include <QtGui>
#include <QtWebKit>

//! [1]

    Browser::Browser(NACS* nacs,QString szUrl)
{

    progress = 0;
    this->setWindowTitle("NACS Acount Manager");
//! [1]

//! [2]
    view = new QWebView(this);

    //QMessageBox *msg=new QMessageBox(QMessageBox::Warning,"dasd","fuck u",QMessageBox::Ok,this);
    //msg->show();

    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(titleChanged(const QString&)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(view->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),this, SLOT(finishLoading()));

    locationEdit = new QLineEdit(this);
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));
    toolBar = addToolBar(tr("Navigation"));
    toolBar->addAction(view->pageAction(QWebPage::Back));
    toolBar->addAction(view->pageAction(QWebPage::Forward));
    toolBar->addAction(view->pageAction(QWebPage::Reload));
    toolBar->addAction(view->pageAction(QWebPage::Stop));
    toolBar->addWidget(locationEdit);
    toolBar->hide();

    view->load(QUrl(szUrl));

    setCentralWidget(view);

    this->m_nacsif=new NACSIF(this);
    this->m_nacs=nacs;
    this->m_nacsif->m_nacs = nacs ;
}
//! [3]

//! [4]
void Browser::keyPressEvent(QKeyEvent *k)
{
    if(k->key()==Qt::Key_Alt)
    {
        toolBar->setHidden(!toolBar->isHidden());
    }
}
void Browser::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void Browser::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    view->load(url);
    view->setFocus();
}
//! [4]

//! [5]
void Browser::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void Browser::setProgress(int p)
{
    progress = p;
    adjustTitle();\
}
//! [5]


//! [6]
void Browser::finishLoading()
{
    progress = 100;
    adjustTitle();
    view->page()->mainFrame()->addToJavaScriptWindowObject("nacs",this->m_nacsif);
    view->page()->mainFrame()->evaluateJavaScript("if(typeof(nacs_main)=='function'){ nacs_main(); }");
}
//! [6]

//! [7]
//! [9]

