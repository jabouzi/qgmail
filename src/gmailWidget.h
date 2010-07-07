#ifndef GMAILWIDGET_H
#define GMAILWIDGET_H
//
#include <QtGui>
#include <QString>
#include <QRect>
#include "ui_gmail.h"
#include "gmail.h"
//

struct emailDate {
    int year;
    int month;
    int day;
    QString shortMonth;
    int hour;
    int minute;
    int second;
};

class GmailWidget : public QWidget, public Ui::Gmail
{
Q_OBJECT
public:
    GmailWidget( QWidget * parent = 0);
    void init(QString);   
    void showWidget();
    void setEmailsList(QList< emailStruct >);
    
private:
    void adjustWindow();    
    void startTimer(int);
    void setMessage(int);
    void getEmailDate(int);
    QString getTimeZoneOffset();
    QRect rec1;
    QRect rec2;
    qreal opac;
    QRegion region;    
    QDesktopWidget *desktop;
    QSize windowSize;     
    int x;
    int y;
    int screenWidth, width; 
    int screenHeight, height;
    int repeat;
    int emailIndex;
    QTimer * timer;
    QTimer * timer2;
    QList< emailStruct > emailsList;
    emailDate eDate;
    
public slots:
    void moveWindow();
    
private slots:
    void showEmails();
    void moveUp();
    void moveDown();
};
#endif




