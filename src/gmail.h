#ifndef GMAIL_H
#define GMAIL_H

#include <QHttp>
#include <QtNetwork>
#include <QXmlStreamReader>
#include "login.h"

struct emailStruct {
    QString title;
    QString summary;
    QString issued;
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
        int getEmailsCount();
        QList< emailStruct > getNewEmails();   
        QList< emailStruct > getAllEmails(); 
        emailStruct emailDetails;
        QList< emailStruct > emailsList;
        QList< emailStruct > totalEmailsList;
                 
    
    private:   
        void getEmails();
        int emailsCount;    
        int currentCount;
        int connectionId;
        QString username;
        QString password;
        bool new_emails;
        bool entryTag;
        QXmlStreamReader xml;  
        QHttp http;     
        QString currentTag;
        QString emailId;
        QStringList emailsIds;   
        Login login; 
        
    private slots:        
        void readData(const QHttpResponseHeader &);    
        void rFinished(int id, bool error);
        void doConnection();
        
    signals:   
        void finished();
        void noConnection();
        void newEmails();
        void noNewEmails();
    
};

#endif
