#ifndef LOGIN_H
#define LOGIN_H

#include <QtGui>
#include "userdata.h"
#include "ui_login.h"

class Login : public QDialog, public Ui::Login
{
Q_OBJECT
public:
    Login( QWidget * parent = 0, Qt::WFlags f = 0 );
    void setPath(QString);
    void init();
    void showWindow();
    user_data getUsernamePassword();

protected:
    void closeEvent(QCloseEvent *);
    
private:
    void setActions();
    QString username;
    QString password;
    QString path;
    Userdata ud;
    user_data p_Data;    
    
private slots:
    void showPassword();
    void savePassword();
    void doLogin();       
    
signals:
    void loginClicked();
};

#endif 
