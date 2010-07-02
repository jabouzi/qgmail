#ifndef DIALOG_H
#define DIALOG_H
//
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QPalette>
#include <QCoreApplication>
#include <QToolTip>
#include <QString>
#include "gmailImpl.h"
//
class Gmail : public QWidget
{
Q_OBJECT     
public:
    Gmail(); 
    
private slots:
    void show_();
    
private:
    QAction *show_action;
    QString path;
    void createActions();
    void createTrayIcon();
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    GmailImpl * gm;
    QAction *quitAction;
};
#endif




