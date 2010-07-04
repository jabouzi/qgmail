#ifndef GMAILWIDGET_H
#define GMAILWIDGET_H
//
#include <QtGui>
#include <QString>
#include <QRect>
#include "ui_gmail.h"
//
class GmailWidget : public QWidget, public Ui::Gmail
{
Q_OBJECT
public:
    GmailWidget( QWidget * parent = 0);
    void init(QString);   
    void showWidget();
    
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
    int screenWidth, width; 
    int screenHeight, height;
    int repeat;
    QTimer * timer;
    
public slots:
    void moveWindow();
    void moveUp();
    
private slots:
    void moveDown();
};
#endif




