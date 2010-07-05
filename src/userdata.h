#ifndef USERDATA_H
#define USERDATA_H

#include <QtCore>
#include <QString>

struct user_data
{
    QString username;
    QString password;
};

class Userdata : public QObject
{  
  Q_OBJECT     
    public:
        Userdata(QObject* = 0); 
        void write_to_binary_file(user_data p_Data, QString);
        user_data read_from_binary_file(QString);
        QString getUsername(QString);
        QString getPassword(QString);
};

#endif
