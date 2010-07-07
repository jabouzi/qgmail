#include "gmail.h"

Gmail::Gmail(QObject* parent) :
    QObject(parent)
{              
    connect(&http, SIGNAL(readyRead(QHttpResponseHeader)),this, SLOT(readData(QHttpResponseHeader))); 
    connect(&login, SIGNAL(loginClicked()),this, SLOT(doConnection())); 
}

void Gmail::init()
{
    new_emails = false;
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
    http.setHost("mail.google.com", QHttp::ConnectionModeHttps);
    http.setUser(username, password);
    http.get("/mail/feed/atom");    
}

void Gmail::readData(const QHttpResponseHeader &resp)
{
    if (resp.statusCode() != 200)
    {
        http.abort();
        emit(noConnection());
    }
    else {
        xml.addData(http.readAll());        
        getEmails();
    }
}

void Gmail::getEmails()
{    
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {                  
            currentTag = xml.name().toString();    
        } else if (xml.isEndElement()) {          
            if (xml.name() == "entry")
            {
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
                    emit(newEmails());                                
                }         
                else
                {
                    new_emails = false;
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
        qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
        http.abort();
    }    
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


