#include "login.h"

Login::Login( QWidget * parent, Qt::WFlags f) : QDialog(parent, f )
{    
    setupUi(this);
    setActions();
}

void Login::setPath(QString lpath)
{    
    path = lpath;        
}

void  Login::showWindow()
{
    show();
    readData(); 
    usernameEdit->setText(username);
    passwordEdit->setText(password);
    if (username != "" and password != "") 
    {
        savePasswordCheck->setChecked(true);
    }
   
}

void Login::init()
{
          
}

//
void Login::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

//
void Login::setActions()
{
    connect(showPasswordCheck, SIGNAL(clicked()), this, SLOT(showPassword()));
    connect(loginButton, SIGNAL(clicked()), this, SLOT(doLogin()));    
}

void Login::showPassword()
{
    passwordEdit->setEchoMode(QLineEdit::Password);
    if (showPasswordCheck->isChecked() == true)
    {
        passwordEdit->setEchoMode(QLineEdit::Normal);
    }
}

void Login::doLogin()
{      
    if (savePasswordCheck->isChecked() == true)
    {
        writeData();
    }
    else
    {
        removeData();
    }
    hide();
    emit(loginClicked());
}

void Login::writeData()
{
    readData();
    if (username != usernameEdit->text() && password != passwordEdit->text())
    {
        QFile file(path+"gmail.dat");
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);   
        out << QString(usernameEdit->text());   
        out << QString(passwordEdit->text());   
    }
}

void Login::readData()
{
    QFile file(path+"gmail.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);   
    in >> username >> password;     
}

void Login::removeData()
{   
    QFile file(path+"gmail.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   
    out << QString("");   
    out << QString("");   
}

QString Login::getUsername()
{
    return usernameEdit->text();
}

QString Login::getPassword()
{
    return passwordEdit->text();
}

