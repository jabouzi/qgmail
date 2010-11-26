#ifndef LOGIN_H
#define LOGIN_H

#include <QtGui>
#include "ui_login.h"

class Login : public QDialog, public Ui::Login
{
Q_OBJECT
public:
    Login( QWidget * parent = 0, Qt::WFlags f = 0 );
    void setPath(QString);
    void init();
    void showWindow();
    QString getUsername();
    QString getPassword();

protected:
    void closeEvent(QCloseEvent *);
    
private:
    void setActions();
    void writeData();
    void readData();
    void removeData();
    QString username;
    QString password;
    QString path;
    
private slots:
    void doLogin();       
    
signals:
    void loginClicked();
};

#endif 
