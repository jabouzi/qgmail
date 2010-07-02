#include <QtGui>

#include "gmail.h"
//
Gmail::Gmail()    
{
    path = QCoreApplication::applicationDirPath();
    if (path.data()[path.size() - 1] != '/') path += "/";
    trayIcon = new QSystemTrayIcon(this); 
    trayIconMenu = new QMenu(this);     
    createActions();
    createTrayIcon();       
    gm = new GmailImpl();    
}

void Gmail::createActions()
{
    show_action = new QAction(tr("Show"), this);
    connect(show_action, SIGNAL(triggered()), this, SLOT(show_()));   
    
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));  
}

void Gmail::createTrayIcon()
{      
    trayIcon->setIcon(QIcon(path+"images/gmail0.png"));
    trayIcon->show();    
    trayIcon->setContextMenu(trayIconMenu);        
    trayIconMenu->addAction(show_action); 
    trayIconMenu->addAction(quitAction);    
}

void Gmail::show_()
{    
    gm->setWindowFlags(Qt::ToolTip);
    gm->init();   
    gm->show_();
}
