#include <QtGui>

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
    gm->connection();
    timer->start(10000);
}

void QtGmail::createActions()
{
    show_action = new QAction(tr("Show"), this);
    connect(show_action, SIGNAL(triggered()), this, SLOT(showWidget()));   
    
    moveup_action = new QAction(tr("Up"), this);
    connect(moveup_action, SIGNAL(triggered()), gmwt, SLOT(moveUp()));  
     
    movedown_action = new QAction(tr("Down"), this);
    connect(movedown_action, SIGNAL(triggered()), gmwt, SLOT(moveDown()));   
    
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));  
    
    connect(gm, SIGNAL(finished()), this, SLOT(displayNewEmails()));
    connect(gm, SIGNAL(newEmails()), this, SLOT(newEmails()));
    connect(gm, SIGNAL(noNewEmails()), this, SLOT(noNewEmails()));
    connect(gm, SIGNAL(noConnection()), this, SLOT(noConnection()));
    connect(timer, SIGNAL(timeout()), this, SLOT(checkEmails()));
}

void QtGmail::createTrayIcon()
{      
    trayIcon->setIcon(QIcon(path+"images/gmail0.png"));
    trayIcon->show();    
    trayIcon->setContextMenu(trayIconMenu);        
    trayIconMenu->addAction(show_action); 
    trayIconMenu->addAction(moveup_action); 
    trayIconMenu->addAction(movedown_action); 
    trayIconMenu->addAction(quitAction);    
}

void QtGmail::showWidget()
{    
    gmwt->setWindowFlags(Qt::ToolTip);
    gmwt->init(path);   
    gmwt->showWidget();
}

void QtGmail::newEmails()
{
    qDebug("New Emails");
    trayIcon->setIcon(QIcon(path+"images/gmail1.png"));
    displayNewEmails();
}

void QtGmail::noNewEmails()
{
    trayIcon->setIcon(QIcon(path+"images/gmail0.png"));
}

void QtGmail::noConnection()
{
    trayIcon->setIcon(QIcon(path+"images/gmail3.png"));
}

void QtGmail::checkEmails()
{
    qDebug("time out");
    gm->connection(); 
}

void QtGmail::displayNewEmails()
{
    emailsList = gm->getNewEmails();
    qDebug(" You hane %d new emails : ",emailsList.size());
    for (int i = 0; i < emailsList.size(); i++)
    {       
        qDebug("Email # %d : ",i+1);
        qDebug("title : %s",emailsList.at(i).title.toLatin1().data());
        qDebug("summary : %s",emailsList.at(i).summary.toLatin1().data());
        qDebug("name : %s",emailsList.at(i).name.toLatin1().data());
        qDebug("email : %s",emailsList.at(i).email.toLatin1().data());
    }
}

void QtGmail::startTimer()
{
    timer->stop();    
    timer->start(30000);
}



