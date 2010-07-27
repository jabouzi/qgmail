#include <QtGui>
 #include <QSound>
#include "qtgmail.h"
//
QtGmail::QtGmail()    
{
    path = QCoreApplication::applicationDirPath();
    if (path.data()[path.size() - 1] != '/') path += "/";
    trayIcon = new QSystemTrayIcon(this); 
    trayIconMenu = new QMenu(this);         
    gmwt = new GmailWidget();    
    gm = new Gmail();
    timer = new QTimer(this);
    createActions();
    createTrayIcon();   
    init();     
}

void QtGmail::init()
{
    gmwt->setWindowFlags(Qt::ToolTip);
    gmwt->init(path);   
    gm->init();
    gm->initLogin(path);
    timer->start(60000);
}

void QtGmail::createActions()
{    
    viewinbox_action = new QAction(tr("View Inbox"), this);
    connect(viewinbox_action, SIGNAL(triggered()), this, SLOT(viewInbox()));   
    
    checknow_action = new QAction(tr("Check Mail Now"), this);
    connect(checknow_action, SIGNAL(triggered()), this, SLOT(checkEmails()));   
    
    tellmeagain_action = new QAction(tr("Tell me Again..."), this);
    connect(tellmeagain_action, SIGNAL(triggered()), this, SLOT(displayAllEmails()));   
    
    about_action = new QAction(tr("About..."), this);
    connect(about_action, SIGNAL(triggered()), this, SLOT(showAboutWidget()));   
    
    aboutqt_action = new QAction(tr("About QT..."), this);
    connect(aboutqt_action, SIGNAL(triggered()), this, SLOT(showAboutQtWidget()));   
    
    quitAction = new QAction(tr("Exit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));   
    
    connect(gm, SIGNAL(finished()), this, SLOT(displayNewEmails()));
    connect(gm, SIGNAL(newEmails()), this, SLOT(newEmails()));
    connect(gm, SIGNAL(noNewEmails()), this, SLOT(noNewEmails()));
    connect(gm, SIGNAL(noConnection()), this, SLOT(noConnection()));
    connect(timer, SIGNAL(timeout()), this, SLOT(checkEmails()));
}

void QtGmail::createTrayIcon()
{      
    /*tooltip avec le nombre d'emails*/
    trayIcon->setIcon(QIcon(path+"images/gmail2.png"));
    trayIcon->show();    
    trayIcon->setContextMenu(trayIconMenu);    
    trayIconMenu->addAction(viewinbox_action); 
    trayIconMenu->addAction(checknow_action); 
    trayIconMenu->addAction(tellmeagain_action); 
    trayIconMenu->addAction(about_action); 
    trayIconMenu->addAction(aboutqt_action); 
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);    
}

void QtGmail::showWidget()
{    
    if (emailsList.size() == 0)
    {
        if (allEmails)
        {
            gmwt->showNoEmailsWidget();
        }
    }
    else
    {
        QSound::play("/usr/share/sounds/purple/receive.wav");
        gmwt->showWidget();
    }
}

void QtGmail::showAboutWidget()
{
    gmwt->showAboutApp();
}

void QtGmail::showAboutQtWidget()
{
    gmwt->showAboutQt();
}

void QtGmail::newEmails()
{
    trayIcon->setIcon(QIcon(path+"images/gmail1.png"));    
    displayNewEmails();    
}

void QtGmail::noNewEmails()
{
    trayIcon->setIcon(QIcon(path+"images/gmail2.png"));
    trayIcon->setToolTip("Qt-GmailNotifier\nYou don't have new emails");
}

void QtGmail::noConnection()
{
    trayIcon->setIcon(QIcon(path+"images/gmail3.png"));
    trayIcon->setToolTip("Connection error!");
}

void QtGmail::checkEmails()
{
    gm->connection(); 
}

void QtGmail::displayNewEmails()
{
    allEmails = false;
    emailsList.clear();
    emailsList = gm->getNewEmails();    
    gmwt->setEmailsList(emailsList);
    showWidget();
    if (gm->getAllEmails().size() == 1)
        trayIcon->setToolTip("Qt-GmailNotifier\nYou have "+QString::number(gm->getAllEmails().size())+" new email");
    else if (gm->getAllEmails().size() > 1)
        trayIcon->setToolTip("Qt-GmailNotifier\nYou have "+QString::number(gm->getAllEmails().size())+" new emails");
}

void QtGmail::displayAllEmails()
{
    allEmails = true;
    emailsList.clear();
    emailsList = gm->getAllEmails();    
    gmwt->setEmailsList(emailsList);    
    showWidget();
}

void QtGmail::viewInbox()
{
    QUrl url; 
    url.setUrl("http://mail.google.com/mail/");
    QDesktopServices::openUrl(url);
}

void QtGmail::startTimer()
{
    timer->stop();    
    timer->start(60000);
}



