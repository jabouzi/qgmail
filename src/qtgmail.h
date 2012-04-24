#ifndef QTGMAIL_H
#define QTGMAIL_H

#include <QObject>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QString>
#include <phonon>
#include "gmailWidget.h"
#include "log.h"


class QtGmail : public QWidget
{
Q_OBJECT     
public:
    QtGmail();
    
private:        
    void init();
    void createActions();
    void createTrayIcon();
    void startTimer();

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




