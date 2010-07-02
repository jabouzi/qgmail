#ifndef GMAILIMPL_H
#define GMAILIMPL_H
//
#include <QtGui>
#include <QString>
#include <QRect>
#include "ui_gmail.h"
//
class GmailImpl : public QWidget, public Ui::Gmail
{
Q_OBJECT
public:
    GmailImpl( QWidget * parent = 0);
    void init();   
    void show_();
    
private:
    void adjustWindow();    
    void startTimer(int);
    QRect rect;
    qreal opac;
    QRegion region;    
    QDesktopWidget *desktop;
    QSize windowSize;     
    int x;
    int y;
    int repeat;
    QTimer * timer;
private slots:
    void moveWindow();
};
#endif




