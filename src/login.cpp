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
    hide();
    emit(loginClicked());
}

void Login::writeData()
{
    readData();
    if (username != usernameEdit->text() && password != passwordEdit->text())
    {
        QFile file("gmail.dat");
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);   
        out << QString(usernameEdit->text());   
        out << QString(passwordEdit->text());   
    }
}

void Login::readData()
{
    QFile file("gmail.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);   
    in >> username >> password;     
}

QString Login::getUsername()
{
    return username;
}

QString Login::getPassword()
{
    return password;
}

