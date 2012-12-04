#include "nacsif.h"
#include "windows.h"
//! [1]
NACSIF::NACSIF(Browser* pBrowser)
{
//! [1]
//! [2]
    this->m_browser=pBrowser;
}

QVariant NACSIF::command(QString szCommand, QVariant param)
{
    if(szCommand == "set_title")
    {
        this->m_browser->setWindowTitle(param.toString());
    }
    else if(szCommand == "set_style")
    {

    }
    else if(szCommand == "set_opacity" && param.canConvert<double>())
    {
        this->m_browser->setWindowOpacity(param.toDouble());
    }
    else if(szCommand == "close" || szCommand == "exit")
    {
        this->m_browser->close();
    }
    else if(szCommand == "display")
    {
        if(param.toBool())
        {
            this->m_browser->show();
        }
        else
        {
            this->m_browser->hide();
        }
    }
    else if((szCommand=="resize" || szCommand=="move") && param.canConvert< QMap<QString,QVariant> >())
    {
        QMap<QString,QVariant> mapSize=param.toMap();
        QRect rct=this->m_browser->geometry();
        if(mapSize.contains("width") && mapSize.value("width").canConvert<int>())
        {
            int w=mapSize.value("width").toInt();
            if(w>=0 && w<=1028)
                 rct.setWidth(w+4);
        }
        if(mapSize.contains("height") && mapSize.value("height").canConvert<int>())
        {
            int h=mapSize.value("height").toInt();
            if(h>=0 && h<=1028)
                rct.setHeight(h+4);
        }
        if(mapSize.contains("x"))
        {
            rct.setX(mapSize.value("x").toInt());
        }
        if(mapSize.contains("y"))
        {
            rct.setY(mapSize.value("y").toInt());
        }
        this->m_browser->setGeometry(rct);
    }

    /* default return true */
    return true;
}
bool NACSIF::mount(QString szSourceVol,QString szName,QString szDestVol){
    szDestVol=szDestVol.toUpper();
    QString szArg="MOUNT "+szName+" "+szSourceVol+" "+szDestVol+" ALL";
    return this->callBase(szArg);

}
bool NACSIF::dismount(QString szDestVol){
    QString szArg="DISMOUNT "+szDestVol;
    return this->callBase(szArg);
}
bool NACSIF::format(QString szVol, QString szName, long nSize){
    return this->m_nacs->format(szVol,szName,nSize);
}

QString NACSIF::getDiskSerial(){
    return QString::number(getHardDriveComputerID(),10);
}
bool NACSIF::callBase(QString szArg){
    PROCESS_INFORMATION ProcessInfo;
    _STARTUPINFOA StartupInfo;
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof StartupInfo ;
    DWORD dwRet=9;
    szArg="nacs_base.exe "+productBaseKey()+" "+szArg;
    char* gv=szArg.toLatin1().data();
    if(CreateProcessA("nacs_base.exe",gv,
        NULL,NULL,FALSE,0,NULL,
        NULL,&StartupInfo,&ProcessInfo))
    {
        WaitForSingleObject(ProcessInfo.hProcess,INFINITE);

        GetExitCodeProcess(ProcessInfo.hProcess,&dwRet);
        CloseHandle(ProcessInfo.hThread);
        CloseHandle(ProcessInfo.hProcess);
        if(dwRet==0) return true;
        else return false;

    }
    else
    {
        return false;
    }
}

QString NACSIF::productBaseKey(){
    QDate dateNow=QDate::currentDate();
    QString szKey=NACS_SK+QString::number( getHardDriveComputerID(),10 )+dateNow.toString("yyyyMMdd");

    return QCryptographicHash::hash(szKey.toAscii(),QCryptographicHash::Md5).toHex();
}

QString NACSIF::hash(QString str)
{
    return  QCryptographicHash::hash(str.toAscii(),QCryptographicHash::Sha1).toHex();
}
bool NACSIF::deleteFormat(QString szName, QString szVol)
{
    QString pathFile = szVol + tr(":/NACS-")+szName;

    if( ! QFile::exists(pathFile) )
    {
        QMessageBox::information(NULL,"NACS Warning","the file you want delete does not exists : "+pathFile);
        return false;
    }
    return QFile::remove(pathFile);

}
void NACSIF::callExplorer(QString szAddress)
{
    ::ShellExecuteA(NULL,"open","explorer.exe",szAddress.toAscii().data(),NULL,SW_SHOWNORMAL);
}
//! [2]
