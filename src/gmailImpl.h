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
    
private:
    void adjustWindow();
    QRect rect;
    qreal opac;
    QRegion region;    
    QDesktopWidget *desktop;
    QSize windowSize;     
};
#endif




