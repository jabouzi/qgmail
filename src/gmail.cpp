#include "gmail.h"

Gmail::Gmail(QObject* parent) :
    QObject(parent)
{              
    connect(&http, SIGNAL(readyRead(QHttpResponseHeader)),this, SLOT(readData(QHttpResponseHeader))); 
    connect(&http, SIGNAL(requestFinished(int,bool)), this, SLOT(rFinished(int,bool)));
    connect(&login, SIGNAL(loginClicked()),this, SLOT(doConnection())); 
}

void Gmail::init()
{
    new_emails = false;
    entryTag = false;
    currentCount = 0;
    xml.clear();
    totalEmailsList.clear();
    emailsList.clear(); 
}

void Gmail::initLogin(QString path)
{      
    login.setPath(path);
    login.showWindow();    
}

void Gmail::connection()
{    
    init();    
    qDebug() << 1234 ;
    http.setHost("mail.googlez.com", QHttp::ConnectionModeHttps);
    http.setUser(username, password);
    http.get("/mail/feed/atom");    
}

void Gmail::readData(const QHttpResponseHeader &resp)
{   
    qDebug() << "****" << resp.toString (); 
    qDebug() << "****" << resp.statusCode (); 
    if (resp.statusCode() != 200)
    {        
        qDebug() << 5678 << resp.statusCode();
        http.abort();
        emit(noConnection());
    }
    else if (resp.statusCode() == 200){
        qDebug() << 5678 << resp.statusCode();
        xml.addData(http.readAll());        
        getEmails();
    }
}

void Gmail::rFinished(int id, bool error)
 {
     if (error) {
         qDebug() << id << error;
         if (id == QHttp::ConnectionRefused) qWarning("Connection Refused");
     }
     else if (id == connectionId) {
         qDebug() << id;         
     }
 }

void Gmail::getEmails()
{    
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {                  
            currentTag = xml.name().toString(); 
            if (xml.name() == "entry")
            {
                entryTag = false;
            }   
        } else if (xml.isEndElement()) {          
            if (xml.name() == "entry")
            {
                entryTag = false;
                totalEmailsList << emailDetails;
                if (!emailsIds.contains(emailId))
                {
                    emailsIds << emailId;
                    emailsList << emailDetails;                    
                }
            }
            else if (xml.name() == "feed")
            {
                emit(finished());
            }
            
        } else if (xml.isCharacters() && !xml.isWhitespace()) {                      
            if (currentTag == "fullcount")
            {               
                bool ok;
                emailsCount = xml.text().toString().toInt(&ok);
                if (emailsCount > currentCount)
                {
                    currentCount = emailsCount;     
                    new_emails = true;   
                    qDebug() << "New emails";
                    emit(newEmails());                                
                }         
                else
                {
                    new_emails = false;
                    qDebug() << "No new emails";
                    emit(noNewEmails());    
                }      
            }
            if (new_emails) 
            {        
                if (currentTag == "id")
                {
                   emailId = xml.text().toString();                    
                }
                if (currentTag == "title")
                {
                    emailDetails.title = xml.text().toString();                    
                }
                else if (currentTag == "summary")
                {
                    emailDetails.summary = xml.text().toString();                    
                }
                else if (currentTag == "issued")
                {
                    emailDetails.issued = xml.text().toString();                    
                }
                else if (currentTag == "name")
                {
                    emailDetails.name = xml.text().toString();                    
                }
                else if (currentTag == "email")
                {
                    emailDetails.email = xml.text().toString();                    
                }               
            }            
        }
    }
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
        qDebug() << 7890;
        qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
        http.abort();
    }    
}

int Gmail::getEmailsCount()
{
    return emailsCount;
}

QList< emailStruct > Gmail::getNewEmails()
{   
    return emailsList;
}

QList< emailStruct > Gmail::getAllEmails()
{   
    return totalEmailsList;
}

void Gmail::doConnection()
{
    username = login.getUsername();
    password = login.getPassword();
    connection();
}


