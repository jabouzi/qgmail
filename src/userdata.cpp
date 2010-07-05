#include "userdata.h"
#include <iostream>
#include <fstream>
using namespace std;

Userdata::Userdata(QObject* parent) :
    QObject(parent)
{              
     
}

void Userdata::write_to_binary_file(user_data p_Data, QString filename)
{
    ofstream out(filename.toAscii().data(), ios::binary);
    out.write((char*)&p_Data.username, sizeof(p_Data.username));
    out.write((char*)&p_Data.password, sizeof(p_Data.password));
    out.close();
}

user_data Userdata::read_from_binary_file(QString filename)
{
    user_data p_Data;
    QString username;
    QString password;
    ifstream in(filename.toAscii().data(), ios::binary);
    in.read((char*)&p_Data.username, sizeof(p_Data.username));
    in.read((char*)&p_Data.password, sizeof(p_Data.password));
    in.close();
    return p_Data;
}

QString Userdata::getUsername(QString filename)
{
    user_data p_Data;
    ifstream in(filename.toAscii().data(), ios::binary);
    in.read((char*)&p_Data, sizeof(p_Data));
    in.close();
    qDebug("000000");
    cout<<p_Data.username.toLatin1().data()<<endl;
    qDebug("333333");
    return p_Data.username;
}

QString Userdata::getPassword(QString filename)
{
    user_data p_Data;
    ifstream in("gmusr.bin", ios::binary);
    in.read((char*)&p_Data, sizeof(p_Data));
    in.close();
    cout<<p_Data.password.toLatin1().data()<<endl;
    return p_Data.password;
}
