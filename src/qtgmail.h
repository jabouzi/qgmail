#ifndef QTGMAIL_H
#define QTGMAIL_H
//
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QString>
#include "gmailWidget.h"
#include "gmail.h"

//
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
    QAction *show_action;
    QAction *moveup_action;
    QAction *movedown_action;
    QString path;
    QTimer * timer;
    QList< emailStruct > emailsList;
    
private slots:
    void showWidget();
    void newEmails();
    void noNewEmails();
    void noConnection();
    void checkEmails();
    void displayNewEmails();
    
};
#endif




