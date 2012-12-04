#include "nacs.h"

NACS::NACS(QString urlServer,QString urlManager)
{

    /* init vars */
    dlgLogin=NULL;
    dlgBrowser = NULL;
    this->isMonLoaded = false;
    this->timerRefresh = new QTimer(this);
    connect(timerRefresh,SIGNAL(timeout()),this,SLOT(refreshOnline()));
    this->urlServer=urlServer;
    this->urlManager=urlManager;
    userLogged = false;
    userOwner = false;

    actionLogin=new QAction(tr("User Login"),this);
    connect(actionLogin,SIGNAL(triggered()),SLOT(showLoginDialog()));

    actionManage=new QAction(tr("Manager Account"),this);
    connect(actionManage,SIGNAL(triggered()),SLOT(showManager()));

    actionExit=new QAction(tr("Exit"),this);
    connect(actionExit,SIGNAL(triggered()),this,SLOT(quitApp()));

    actionValidProcess = new QAction(tr("Enable Valid Process"),this);
    actionValidProcess->setCheckable(true);
    /* find if the NACSVP enabled */
    QSettings *regNacs=new QSettings(NACS_REG_PATH,QSettings::NativeFormat);
    QString szHashReg = regNacs->value("0","").toString();
    QString szHashVp = tr(NACS_SK)+"0";
    szHashVp = QCryptographicHash::hash(szHashVp.toAscii(),QCryptographicHash::Sha1).toHex();
    if( szHashReg == szHashVp ) actionValidProcess->setChecked(false);
    else actionValidProcess->setChecked(true);
    delete regNacs;
    connect(actionValidProcess,SIGNAL(triggered(bool)),this,SLOT(triggleValidProcess(bool)));

    actionRunValid = new QAction(tr("Run Valid Process"),this);
    connect(actionRunValid,SIGNAL(triggered()),this,SLOT(toggleRunValid()));

    menuTray=new QMenu(NULL);
    menuTray->addAction(actionLogin);
    menuTray->addAction(actionManage);
    menuTray->addSeparator();
    menuTray->addAction(actionValidProcess);
    menuTray->addAction(actionRunValid);
    menuTray->addSeparator();
    menuTray->addAction(actionExit);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/icon.png"));
    trayIcon->setContextMenu(menuTray);

    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActived(QSystemTrayIcon::ActivationReason)));

    trayIcon->show();
    showMessage("NACS is running here!");



}
void NACS::userLogin(QString szUsername, QString szPassword)
{
    if( this->userLogged ) return this->userLogout();
    QDate dateNow=QDate::currentDate();
    QTime timeNow=QTime::currentTime();
    QString szTime = dateNow.toString("yyyyMMdd")+timeNow.toString("HH");
    QString szSerial  =  QString::number( getHardDriveComputerID(),10 );


    szPassword = QCryptographicHash::hash(szPassword.toAscii(),QCryptographicHash::Sha1).toHex();

    QString szVerify = szUsername + szSerial + szTime + NACS_WEB_SK;
    szVerify = QCryptographicHash::hash(szVerify.toAscii(),QCryptographicHash::Sha1).toHex();

    QString szUrl=QString("/server.php?user=%1&pass=%2&serial=%3&verify=%4").arg(szUsername,szPassword, szSerial , szVerify );

    /* save username and password */
    this->userName = szUsername;
    this->userPass = szPassword;

    httpServer = new QHttp(this);
    connect(httpServer, SIGNAL(done(bool)), this,SLOT(callbackUserLogin(bool)));

    httpServer->setHost(urlServer);

    httpServer->get(szUrl);
}
void NACS::callbackUserLogin(bool bSuccess)
{
    if(httpServer->state() != QHttp::Connected )
    {
        showMessage("Cannot connect to the server!");
    }
    else
    {
        QString szBody=httpServer->readAll();
        QStringList listBody=szBody.split("|");
        if(listBody.length()!=4)
        {
            showMessage(szBody);
            return ;
        }
        /* verify this message  */
        QDate dateNow=QDate::currentDate();
        QTime timeNow=QTime::currentTime();
        QString szTime = dateNow.toString("yyyyMMdd")+timeNow.toString("HH");

        QString szVerifyBody = listBody[0] + "|" + listBody[1] + "|" + listBody[2] +"|" + NACS_WEB_SK + szTime;
        szVerifyBody = QCryptographicHash::hash(szVerifyBody.toAscii(),QCryptographicHash::Sha1).toHex();
        if( szVerifyBody != listBody[3] )
        {
            showMessage("Callback Message Invalid!!");
            return ;
        }

        this->userLogged = true;
        this->userOwner = listBody[0]=="1" ? true : false;
        this->userAccess = listBody[1].split("#");
        this->userPrivilege = listBody[2].split("#");
        mapMountedDrivers.clear();
        actionLogin->setText("User Logout");
        showMessage("User Login Successed.");
        refreshOnline();
        this->userMountAll();
        this->ftpCreateAccounts();
    }
    return ;
}

void NACS::userLogout()
{
    if( !this->userLogged ) return;
    ftpServiceStop();
    this->userDismountAll();
    this->userLogged = false;
    actionLogin->setText("User Login");
    showMessage("User Logout Successed.");

}

void NACS::userMountAll()
{
    if( !userLogged ) return;
    for( int i=0; i<userAccess.length(); i++ )
    {
        QString szUserAccess = userAccess[i];
        QStringList listAccess = szUserAccess.split(",");
        if( listAccess.length()!=3 ) continue;
        QString szAccess = "READ";
        if( listAccess[2].at(0) == QChar('1') ) szAccess="ALL";
        QString szDriver =getFreeDriver();
        bool bMount = mount(listAccess[1],listAccess[0],szDriver,szAccess);
        if(bMount)
        {
            mapMountedDrivers[ listAccess[0]+"#"+listAccess[1] ] = szDriver;
            showMessage(listAccess[0]+" : Mounted.");
        }
        else showMessage(listAccess[0]+" : Mount Failed.");
    }
    /* Load to filter drive */
    this->loadMonDriver();
    DWORD nb,dwDriveSet;
    dwDriveSet = this->productDriveWord();
    if ( ! DeviceIoControl(	hDevice, IOCTL_FILEMON_SETDRIVES,
                                                            &dwDriveSet, sizeof(dwDriveSet),
                                                            &dwDriveSet, sizeof(dwDriveSet),
                                                            &nb, NULL ) )
    {
        QMessageBox::information(NULL,"NACS Error","Could not pass drive set to nacs mon.");
        return ;
    }
}
void NACS::userDismountAll()
{
    QStringList listMountedDrivers = mapMountedDrivers.values();
    for( int i=0; i<listMountedDrivers.length(); i++ )
    {
        QString szUserAccess = userAccess[i];
        QStringList listAccess = szUserAccess.split(",");
        if( listAccess.length()!=3 ) continue;
        dismount(listMountedDrivers[i]);
        showMessage(listAccess[0]+" : Dismounted.");
    }
    mapMountedDrivers.clear();
    //UnloadDeviceDriver( L"NACS_MON" );
    DWORD nb,dwDriveSet;
    dwDriveSet = 0;
    if ( ! DeviceIoControl(	hDevice, IOCTL_FILEMON_SETDRIVES,
                                                            &dwDriveSet, sizeof(dwDriveSet),
                                                            &dwDriveSet, sizeof(dwDriveSet),
                                                            &nb, NULL ) )
    {
        QMessageBox::information(NULL,"NACS Error","Could not pass drive set to nacs mon.");
        return ;
    }
}

void NACS::ftpCreateAccounts()
{
    if( ! userLogged ) return ;
    int nAccounts = 0;
    QString szSerial = QString::number( getHardDriveComputerID(),10 );
    QString txtPrivilege="";
    QString szSrcVol,szName,szDestVol,szUser,szAccess,szUsername,szPassword;
    QDate dateNow=QDate::currentDate();
    QString szDate = dateNow.toString("yyyyMMdd");
    long nPrivilege;
    for( int i=0; i<userPrivilege.length(); i++ )
    {
        QString szPrivilege=userPrivilege[i];
        QStringList listPrivilege = szPrivilege.split(",");
        if( listPrivilege.length() != 4 )  continue;
        szUser = listPrivilege[0]; szName = listPrivilege[1];szSrcVol = listPrivilege[2]; szAccess = listPrivilege[3];
        if(szAccess.length() != 4) continue ;
        szDestVol = mapMountedDrivers.value(szName+"#"+szSrcVol,NULL);
        if( szDestVol == NULL ) continue;
        /* product username and password */
        szUsername = szUser + szSerial + szName + szSrcVol;
        szUsername = QCryptographicHash::hash(szUsername.toAscii(),QCryptographicHash::Sha1).toHex();
        szUsername = szUsername.left(10);
        szPassword = szUsername + NACS_WEB_SK + szDate;
        szPassword = QCryptographicHash::hash(szPassword.toAscii(),QCryptographicHash::Sha1).toHex();
        szPassword = szPassword.left(10);
        szPassword = md5(szPassword,true).toUpper();
        nPrivilege = 131072;
        if( szAccess.at(1) == QChar('1') ) nPrivilege += 2;
        if( szAccess.at(2) == QChar('1') ) nPrivilege += 65541;
        if( szAccess.at(3) == QChar('1') ) nPrivilege += 262152;
        szAccess=QString::number(nPrivilege,10);

        txtPrivilege += QString("<user username=\"%1\" password=\"%2\" alias=\"%1\" privilege=\"%3\" work_dir=\"%4:\\\" welcome_msg=\"welcome to NACS FTP\" disabled=\"no\" />\r\n").arg(
                        szUsername,szPassword,szAccess,szDestVol
                );
        nAccounts++;
    }
    if( nAccounts == 0 ) return ;
    txtPrivilege = "<users>\r\n" + txtPrivilege +"</users>";
    QFile file("plugin_ftp\\ftpusers.xml");
    file.open(QIODevice::WriteOnly);
    file.write(txtPrivilege.toAscii(),txtPrivilege.length());
    file.close();
    ftpServiceStart();
}

bool NACS::ftpExists()
{
    return QFile::exists("plugin_ftp/nacs_ftp.exe");
}
void NACS::ftpServiceStart()
{
    ftpServiceStop();
    /* create process */
    PROCESS_INFORMATION ProcessInfo;
    _STARTUPINFOA StartupInfo;
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof StartupInfo ;
    StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = SW_HIDE;

    if(CreateProcessA("plugin_ftp\\nacs_ftp.exe","nacs_ftp.exe /nontservice",
        NULL,NULL,FALSE,0,NULL,
        NULL,&StartupInfo,&ProcessInfo))
    {

        long pidBase= ProcessInfo.dwProcessId;
        QSettings *regNacs=new QSettings(NACS_REG_PATH,QSettings::NativeFormat);
        QString szHashVp =  tr(NACS_SK)+QString::number(pidBase);
        szHashVp = QCryptographicHash::hash(szHashVp.toAscii(),QCryptographicHash::Sha1).toHex();
        regNacs->setValue(QString::number(pidBase),szHashVp);


    }
    else
    {
        return ;
    }
    showMessage("Ftp Service Started.");
}
void NACS::ftpServiceStop()
{
    DWORD idProcess = verifyProcess("nacs_ftp.exe");
    if( idProcess == 0 ) return ;
    HANDLE   hProcess;
    hProcess=OpenProcess(1,0,idProcess);
    TerminateProcess(hProcess,0);
    CloseHandle(hProcess);
}

bool NACS::mount(QString szSourceVol,QString szName,QString szDestVol,QString szAccess){
    szDestVol=szDestVol.toUpper();
    QString szArg="MOUNT "+szName+" "+szSourceVol+" "+szDestVol+" "+szAccess;
    return this->callBase(szArg);

}
bool NACS::dismount(QString szDestVol){
    QString szArg="DISMOUNT "+szDestVol;
    return this->callBase(szArg);
}
bool NACS::format(QString szVol, QString szName, long nSize){
    QString szArg="FORMAT "+szName+" "+szVol+" "+QString::number(nSize,10);
    return this->callBase(szArg);
}

void NACS::showLoginDialog()
{
    if( this->userLogged ) return this->userLogout();
    if(dlgLogin && !dlgLogin->isHidden()) return ;
    dlgLogin=new DialogLogin(this);
    dlgLogin->show();
}
void NACS::showManager()
{
    if(dlgBrowser && !dlgBrowser->isHidden()) return ;
    dlgBrowser=new Browser(this,this->urlManager);
    dlgBrowser->show();
}
void NACS::quitApp()
{
    userLogout();
    UnloadDeviceDriver( L"NACS_MON" );
    CloseHandle(hDevice);
    trayIcon->hide();
    QCoreApplication::instance()->quit();
}

void NACS::showMessage(QString szMessage)
{
    trayIcon->showMessage("NACS Message",szMessage,QSystemTrayIcon::Information,2000);
}
bool NACS::callBase(QString szArg){
    PROCESS_INFORMATION ProcessInfo;
    _STARTUPINFOA StartupInfo;
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof StartupInfo ;
    DWORD dwRet=9;
    szArg="nacs_base.exe "+productBaseKey()+" "+szArg;
    char* gv=szArg.toAscii().data();

    /* create mutex for pid register  */
    HANDLE hMutex = ::CreateMutexW(NULL,FALSE,L"NACS_PID_REG");


    if(CreateProcessA("nacs_base.exe",gv,
        NULL,NULL,FALSE,0,NULL,
        NULL,&StartupInfo,&ProcessInfo))
    {
        /* reg pid*/
        long pidBase= ProcessInfo.dwProcessId;
        QSettings *regNacs=new QSettings(NACS_REG_PATH,QSettings::NativeFormat);
        QString szHashVp =  tr(NACS_SK)+QString::number(pidBase);
        szHashVp = QCryptographicHash::hash(szHashVp.toAscii(),QCryptographicHash::Sha1).toHex();
        regNacs->setValue(QString::number(pidBase),szHashVp);
        ::ReleaseMutex(hMutex);
        ::CloseHandle(hMutex);

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

QString NACS::productBaseKey(){
    QDate dateNow=QDate::currentDate();
    QString szKey=NACS_SK+QString::number( getHardDriveComputerID(),10 )+dateNow.toString("yyyyMMdd");

    return QCryptographicHash::hash(szKey.toAscii(),QCryptographicHash::Md5).toHex();
}

QStringList NACS::getAllFreeDrivers()
{
    QStringList listDrivers;
    QStringList listFreeDrivers;
    char pSzDrivers[MAX_PATH];
    memset(pSzDrivers,0,MAX_PATH);
    ::GetLogicalDriveStringsA(MAX_PATH,pSzDrivers);
    for(int i=0; i<MAX_PATH; i+=4)
    {
        char ch = pSzDrivers[i];
        if( ch=='\0' ) break;
        listDrivers.append(QString(ch));
    }
    for(char ch='Z'; ch>'C' ; ch--  )
    {
        QString szDriver = QString(ch);
        if( listDrivers.contains(szDriver,Qt::CaseInsensitive) == false )
        {
            listFreeDrivers.append(szDriver);
        }
    }
    return listFreeDrivers ;

}
QString NACS::getFreeDriver()
{
    return getAllFreeDrivers().at(0);
}
QString NACS::md5(QString str, bool bFuck)
{
    QString szRet;
    szRet=QCryptographicHash::hash(str.toAscii(),QCryptographicHash::Md5).toHex();
    if(bFuck)
    {
        QString szMirror = szRet;
        szRet ="";
        int nGroup,nOffset;
        for(int i=0;i<16;i++)
        {
            nGroup = i/4;
            nOffset = nGroup*4 + 3 - i % 4;
            szRet.append( szMirror.mid(nOffset*2,2) );
        }
    }
    return szRet;
}
void NACS::iconActived(QSystemTrayIcon::ActivationReason reason)
{
    trayIcon->contextMenu()->show();
}

bool NACS::createDesktopShotCut( QString strSourcePath )
{
      TCHAR   szPath[MAX_PATH];
      if(SUCCEEDED( SHGetFolderPath(NULL,CSIDL_DESKTOP  , NULL,0,szPath) ))
      {
          QString pathLink = QString::fromWCharArray(szPath);
          QStringList listSplitSource = strSourcePath.split("\\");
          pathLink += tr("\\")+listSplitSource.last() +tr(".lnk");

          QString pathLinkTarget = QApplication::applicationDirPath();
          pathLinkTarget = pathLinkTarget.replace("/","\\");
          pathLinkTarget +=  tr("\\nacs_entry.exe");//+strSourcePath;
          /* generate link target */
          pathLinkTarget.toWCharArray(szPath);
          /* generate link argument */
          /* generate link icon */
          WCHAR   szArguments[MAX_PATH];
          memset(szArguments,0,MAX_PATH);
          strSourcePath.toWCharArray(szArguments);
          /* create shotcut */
          bool bSuccess=create_windows_shotcut( szPath, pathLink.toAscii().data() ,szArguments,szArguments);
          if( bSuccess )
            showMessage(tr("Create Link Successed : ") + listSplitSource.last() );
          else
            showMessage(tr("Create Link Failed : ") + listSplitSource.last() );
          return true;
      }
    return false;
}
void NACS::triggleValidProcess(bool bValid)
{
    QSettings *regNacs=new QSettings(NACS_REG_PATH,QSettings::NativeFormat);
    if( bValid  )
    {
        regNacs->setValue("0","NACS");
    }
    else
    {
        QString szHashVp =  tr(NACS_SK)+"0";
        szHashVp = QCryptographicHash::hash(szHashVp.toAscii(),QCryptographicHash::Sha1).toHex();
        regNacs->setValue("0",szHashVp);
    }
    delete regNacs;
}
void NACS::toggleRunValid()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("Open Executable File"),NULL, tr("Executable File (*.exe)"));
    createDesktopShotCut(fileName.replace("/","\\"));
}
void NACS::publicShowLoginDialog()
{
    return showLoginDialog();
}
DWORD NACS::productDriveWord()
{
    DWORD dwDrives = 0;
    QStringList listMountedDrivers = mapMountedDrivers.values();
    for( int i=0; i<listMountedDrivers.length(); i++ )
    {
       QString szDrive = listMountedDrivers[i];
       char chDrive = szDrive[0].toAscii();
       DWORD dwMask = 1;
       dwMask = dwMask << (chDrive-'A');
       dwDrives |= dwMask;
    }
    return dwDrives;
}
bool NACS::loadMonDriver()
{
    if( this->isMonLoaded ) return true;
    /* Load Filter Driver */
    if(!QFile::exists("nacs_mon.sys"))
    {
        QMessageBox::information(NULL,"NACS Error","Cannot find file : nacs_mon.sys");

        return false;
    }
    DWORD error;
    QString pathSysMon= QDir::currentPath().replace("/","\\") + tr("\\nacs_mon.sys");
    WCHAR wszPathMon[MAX_PATH];
    memset(wszPathMon,0,MAX_PATH);
    pathSysMon.toWCharArray(wszPathMon);
    if(!LoadDeviceDriver(L"NACS_MON",wszPathMon,&hDevice,&error))
    {
        QMessageBox::information(NULL,"NACS Error","Load nacs_mon.sys Failed");
         UnloadDeviceDriver( L"NACS_MON" );
        return false;
    }
    DWORD nb;
    if ( ! DeviceIoControl(	hDevice, IOCTL_FILEMON_ZEROSTATS, NULL, 0, NULL, 0, &nb, NULL ) )
    {
        QMessageBox::information(NULL,"NACS Error","Could not Access Driver when zerostats");
        UnloadDeviceDriver( L"NACS_MON" );
       return false;
    }
    FilterDefinition.logreads = FALSE;
    FilterDefinition.logwrites = FALSE;
    FilterDefinition.excludefilter[0] = 0;
    FilterDefinition.includefilter[0] = 0;
    if ( ! DeviceIoControl(hDevice, IOCTL_FILEMON_SETFILTER,(PVOID) &FilterDefinition, sizeof(FilterDefinition), NULL, 0, &nb, NULL ) )
    {
        QMessageBox::information(NULL,"NACS Error","Could not Access Driver when SetFilter");
        UnloadDeviceDriver( L"NACS_MON" );
        return false;
    }

    if ( ! DeviceIoControl(hDevice, IOCTL_FILEMON_STARTFILTER,NULL, 0, NULL, 0, &nb, NULL ) )
    {
        QMessageBox::information(NULL,"NACS Error","Could not Access Driver when start");
        UnloadDeviceDriver( L"NACS_MON" );
        return false;
    }
     this->isMonLoaded = true;
    return true;
}
void NACS::callExplorer(QString szAddress)
{
    ::ShellExecuteA(NULL,"open",szAddress.toAscii().data(),NULL,NULL,SW_SHOWNORMAL);
}
void NACS::refreshOnline()
{
    if(this->userLogged && !timerRefresh->isActive())
    {
        timerRefresh->setInterval(5*60*1000);
        timerRefresh->start();
    }
    else if( !userLogged && timerRefresh->isActive() )
    {
        timerRefresh->stop();
        return ;
    }

    QString szSerial=QString::number( getHardDriveComputerID(),10 );
    QString szIpAddress = QHostInfo::fromName(QHostInfo::localHostName()).addresses().at(3).toString();
    QString szVerify = szSerial+szIpAddress+QDate::currentDate().toString("yyyyMMdd")+NACS_WEB_SK;
    szVerify = QCryptographicHash::hash(szVerify.toAscii(),QCryptographicHash::Sha1).toHex();
    QString szUrl=QString("/online.php?serial=%1&ip=%2&verify=%3").arg(szSerial,szIpAddress, szVerify );

    httpServer = new QHttp(this);

    httpServer->setHost(urlServer);

    httpServer->get(szUrl);
}
