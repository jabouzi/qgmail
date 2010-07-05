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
    QString filename = "gmusr.bin";
    qDebug("111111111");
    ud.read_from_binary_file(filename);
    //ud.getUsername(filename);
    //~ qDebug("%s",ud.getUsername(filename).toLatin1().data());
    //~ qDebug("%s",p_Data.password.toLatin1().data());
    //~ usernameEdit->setText("skander");
    //~ passwordEdit->setText("jabouzi"); 
    qDebug("222222222");
}

void Login::init()
{
    //ud.init(path+"gmusr.bin");
    //p_Data = ud.read_from_binary_file();
    //~ qDebug("%s",p_Data.username.toLatin1().data());
    //~ usernameEdit->setText(p_Data.username);
    //~ passwordEdit->setText(p_Data.password);       
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
    //~ connect(savePasswordCheck, SIGNAL(clicked()), this, SLOT(savePassword()));    
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

void Login::savePassword()
{        
    QString filename = path+"gmusr.bin";
    p_Data.username = usernameEdit->text();
    p_Data.password = passwordEdit->text();    
    ud.write_to_binary_file(p_Data,filename);
    //~ p_Data = getUsernamePassword();
    //~ qDebug("%s",p_Data.username.toLatin1().data());
}

void Login::doLogin()
{      
    if (savePasswordCheck->isChecked() == true)
    {
        savePassword();
    }
    hide();
    emit(loginClicked());
}

user_data Login::getUsernamePassword()
{
    QString filename = path+"gmusr.bin";
    return ud.read_from_binary_file(filename);
}
