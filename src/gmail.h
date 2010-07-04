#ifndef GMAIL_H
#define GMAIL_H

#include <QHttp>
#include <QtNetwork>
#include <QXmlStreamReader>
#include <QtSql>

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
        void connection();   
        QList< emailStruct > getNewEmails(); 
        
        emailStruct emailDetails;
        QList< emailStruct > emailsList;
                 
    
    private:    
        void init();
        void getEmails();
        int emailsCount;    
        int currentCount;
        int connectionId;
        bool new_emails;
        QXmlStreamReader xml;  
        QHttp http;     
        QString currentTag;
        QString emailId;
        QStringList emailsIds;        
        
    private slots:        
        void readData(const QHttpResponseHeader &);    
        
        
    signals:   
        void finished();
        void noConnection();
        void newEmails();
        void noNewEmails();
    
};

#endif
