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
    void showNoEmailsWidget();
    void showAboutApp();
    void showAboutQt();
    void setEmailsList(QList< emailStruct >);
    
private:
    void adjustWindow();    
    void startTimer(int);
    void setMessage(int);
    void getEmailDate(int);
    QString getTimeZoneOffset();
    void setNoEmailsMessage();
    void setAboutMessage();
    void setAboutQtMessage();
    int getTopPanel();
    QRect rec1;
    QRect rec2;
    qreal opac;
    QRegion region;    
    QDesktopWidget *desktop;
    QSize windowSize;     
    int x;
    int y;
    int screenWidth, width, originalWidth; 
    int screenHeight, height, originalHeight;
    int repeat;
    int emailIndex;
    int var1, var2, var3;
    QTimer * timer;
    QTimer * timer2;
    QList< emailStruct > emailsList;
    emailDate eDate;
    QString path;
    
public slots:
    void moveWindow();
    
private slots:
    void showEmails();
    void moveUp();
    void moveDown();
};
#endif




