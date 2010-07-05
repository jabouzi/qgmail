#ifndef GMAIL_H
#define GMAIL_H

#include <QHttp>
#include <QtNetwork>
#include <QXmlStreamReader>
#include <QtSql>
#include "login.h"

struct emailStruct {
    QString title;
    QString summary;
    QString name;
    QString email;
};

class Gmail : public QObject
{  
  Q_OBJECT     
    public:
        Gmail(QObject* = 0); 
        void init();
        void initLogin(QString);      
        void connection();  
        QList< emailStruct > getNewEmails();         
        emailStruct emailDetails;
        QList< emailStruct > emailsList;
                 
    
    private:   
        void getEmails();
        int emailsCount;    
        int currentCount;
        int connectionId;
        QString username;
        QString password;
        bool new_emails;
        QXmlStreamReader xml;  
        QHttp http;     
        QString currentTag;
        QString emailId;
        QStringList emailsIds;   
        Login login; 
        
    private slots:        
        void readData(const QHttpResponseHeader &);    
        void doConnection();
        
    signals:   
        void finished();
        void noConnection();
        void newEmails();
        void noNewEmails();
    
};

#endif
