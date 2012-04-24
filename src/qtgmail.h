#ifndef QTGMAIL_H
#define QTGMAIL_H
//
#include <QObject>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QString>
#include <phonon>
//#include <QxtApplication>
//#include <QxtNativeEventFilter>
#include "gmailWidget.h"
#include "log.h"
//#include <X11/Xlib.h>

//
class QtGmail : public QWidget
{
Q_OBJECT     
public:
    QtGmail();
    //bool x11EventFilter(XEvent* event);
    
private:        
    void init();
    void createActions();
    void createTrayIcon();
    void startTimer();
    //static bool myEventFilter(void *message, long *result);

    //QCoreApplication::EventFilter myEventFilter
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    GmailWidget * gmwt;
    Gmail * gm;
    QAction *quitAction;   
    QAction *viewinbox_action; 
    QAction *checknow_action; 
    QAction *tellmeagain_action; 
    QAction *about_action; 
    QAction *aboutqt_action; 
    QString path;
    QTimer * timer;
    QList< emailStruct > emailsList;
    int emailsCount;
    bool allEmails;
    Phonon::MediaObject *music;
    Log *pLog;
protected:
    //bool myEventFilter2(QObject * target , QEvent * event);
    
private slots:
    void showWidget();
    void newEmails();
    void noNewEmails();
    void noConnection();
    void checkEmails();
    void displayNewEmails();
    void displayAllEmails();
    void viewInbox();
    void showAboutWidget();
    void showAboutQtWidget();   
    
};
#endif




