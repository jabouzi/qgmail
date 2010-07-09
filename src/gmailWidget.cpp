#include "gmailWidget.h"
//
GmailWidget::GmailWidget( QWidget * parent) 
    : QWidget(parent)
{    
    setupUi(this);    
    desktop = QApplication::desktop();
    opac = 0.9;    
    repeat = 0;    
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveWindow()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(showEmails()));
}

void GmailWidget::init(QString lpath)
{    
    path = lpath;
    pLog = new Log(path+"gmail.log");
    this->setWindowOpacity(opac);    
    label->setTextFormat(Qt::RichText);
    label->setWordWrap(true);
} 

void GmailWidget::showWidget()
{
    var1 = 7; var2 = 8; var3 = 14;
    adjustWindow();
    setMessage(0);    
    repeat = 0;
    show();
    startTimer(90);
    emailIndex = 1;
}

void GmailWidget::showNoEmailsWidget()
{
    var1 = 7; var2 = 8; var3 = 14;
    adjustWindow();
    setNoEmailsMessage();    
    repeat = 0;
    show();
    startTimer(90);
    emailIndex = 1;
}

void GmailWidget::showAboutApp()
{
    var1 = 10; var2 = 11; var3 = 20;
    adjustWindow();
    setAboutMessage();    
    repeat = 0;
    show();
    startTimer(90);
    emailIndex = 1;
}

void GmailWidget::showAboutQt()
{
    var1 = 52; var2 = 53; var3 = 104;
    //setGeometry(500,y,500,height);
    adjustWindow();
    setAboutQtMessage();    
    repeat = 0;
    show();
    startTimer(90);
    emailIndex = 1;
}

void GmailWidget::adjustWindow()
{    
    windowSize = size();      
    width = windowSize.width(); 
    height = windowSize.height(); 
    QRect rec1 = desktop->screenGeometry (0);    
    QRect rec2 = desktop->availableGeometry (0);    
    height = 0, x = rec1.width() - width, y = rec1.height() - getTopPanel();    
    setGeometry(x,y,width,height);
    pLog->Write("W : "+QString::number(width)); 
    pLog->Write("H : "+QString::number(height)); 
    pLog->Write("RW : "+QString::number(rec1.width())); 
    pLog->Write("RH : "+QString::number(rec1.height())); 
    pLog->Write("RW : "+QString::number(rec2.width())); 
    pLog->Write("RH : "+QString::number(rec2.height())); 
}

void GmailWidget::moveWindow()
{      
    repeat++;   
    //qDebug("repeat : %d",repeat); 
    if (repeat < var1)
    {
        moveUp();
    }
    else if (repeat >= var1 && repeat < var2)
    {
        timer->stop();
        timer2->start(5000);        
    }
    else if (repeat >= var2 && repeat < var3)
    {
        moveDown();
    }
    else if (repeat >= var3)
    {
        timer->stop();
    }
}

void GmailWidget::moveUp()
{
    y = y - 11;
    height = height + 11;
    setGeometry(x,y,width,height);   
    startTimer(90); 
}

void GmailWidget::moveDown()
{
    y = y + 11;
    height = height - 11;
    setGeometry(x,y,width,height);
    startTimer(90);
    //~ qDebug("Repeat D: %d - %d",y,height); 
}

void GmailWidget::showEmails()
{    
    if (emailIndex < emailsList.size())
    {
        qDebug("emailIndex : %d",emailIndex);    
        setMessage(emailIndex);   
        emailIndex++;
    }
    else
    {    
        timer2->stop();
        timer->start(90); 
    }
}

void GmailWidget::setMessage(int index)
{        
    QImage image(path+"images/gmail4.png");
    label_3->setPixmap(QPixmap::fromImage(image));
    label->setGeometry( 69, 5, 291, 57 );
    QString printedDate;
    getEmailDate(index);
    QDate date = QDate::currentDate();
    if (date.day() > eDate.day)
        printedDate = eDate.shortMonth+" "+QString::number(eDate.day);
    else
        printedDate = QString::number(eDate.hour)+":"+QString::number(eDate.minute);
    QString inboxSymbol = "»";
    QString text = "<b style='color:red;'>"+QString::fromUtf8(inboxSymbol.toLatin1().data())+"</b>"+QString::number(index+1)+" of "+QString::number(emailsList.size())+" - "+printedDate+" <b>"+emailsList.at(index).name+"</b><br />";
    text += "<b>"+emailsList.at(index).title+"</b><br />";
    text += "<i>"+emailsList.at(index).summary+"</i><br />";
    label->setText(text);  
}

void GmailWidget::setNoEmailsMessage()
{        
    QImage image(path+"images/gmail4.png");
    label_3->setPixmap(QPixmap::fromImage(image));
    label->setGeometry( 69, 5, 291, 57 );
    QString text = "Your inbox contains no unread conversations.";
    label->setText(text);  
}

void GmailWidget::setAboutMessage()
{    
    QImage image(path+"images/qt-gmail.png");
    label_3->setPixmap(QPixmap::fromImage(image));
    label->setGeometry( 69, 5, 291, 90 );
    QString cp = "©";
    QString text = "<b> Qt-GmailNotifier Clone application 0.1</b> <br>Copyright " +  QString::fromUtf8(cp.toLatin1().data()) + " 2009 Skander Jabouzi skander@skanderjabouzi.com<br>";
            text += " This is a free software distributed under the terms of the GNU <br> General Public License version 3<br>(http://www.gnu.org/licenses/gpl-3.0.html)";     
    label->setText(text);  
}

void GmailWidget::setAboutQtMessage()
{    
    QImage image(path+"images/qt.png");
    label_3->setPixmap(QPixmap::fromImage(image));
    label->setGeometry( 69, 5, 291, 550 );
    QString text = "<p style=\"margin: 0px 0px;\"><!--StartFragment--><span style=\"font-size: large; font-weight: 600;\">About Qt</span></p>";
    text += "<p style=\"margin: 5px 0px; text-indent: 0px;\">This program uses Qt version "+QString(QT_VERSION_STR)+".</p>";
    text +=  "<p style=\"margin: 5px 0px; text-indent: 0px;\"><!--StartFragment-->Qt is a C++ toolkit for cross-platform application development.</p>";
    text += "<p style=\"margin: 5px 0px; text-indent: 0px;\">Qt provides single-source portability across MS&nbsp;Windows, Mac&nbsp;OS&nbsp;X, Linux, and all major commercial Unix variants. Qt is also available for embedded devices as Qt for Embedded Linux and Qt for Windows CE.</p>";
    text += "<p style=\"margin: 5px 0px; text-indent: 0px;\">Qt is available under three different licensing options designed to accommodate the needs of our various users.</p>";
    text += "<p style=\"margin: 5px 0px; text-indent: 0px;\">Qt licensed under our commercial license agreement is appropriate for development of proprietary/commercial software where you do not want to share any source code with third parties or otherwise cannot comply with the terms of the GNU LGPL version 2.1 or GNU GPL version 3.0.</p>";
    text += "<p style=\"margin: 5px 0px; text-indent: 0px;\">Qt licensed under the GNU LGPL version 2.1 is appropriate for the development of Qt applications (proprietary or open source) provided you can comply with the terms and conditions of the GNU LGPL version 2.1.</p>";
    text += "<p style=\"margin: 5px 0px; text-indent: 0px;\">Qt licensed under the GNU General Public License version 3.0 is appropriate for the development of Qt applications where you wish to use such applications in combination with software subject to the terms of the GNU GPL version 3.0 or where you are otherwise willing to comply with the terms of the GNU GPL version 3.0.</p>";
    text += "<p style=\"margin: 5px 0px; text-indent: 0px;\">Please see <a href=\"http://qt.nokia.com/products/licensing\"><span style=\"text-decoration: underline; color: rgb(0, 0, 255);\">qt.nokia.com/products/licensing</span></a> for an overview of Qt licensing.</p>";
    text += "<p style=\"margin: 5px 0px; text-indent: 0px;\">Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).</p>";
    text += "<p style=\"margin: 5px 0px; text-indent: 0px;\">Qt is a Nokia product. See <a href=\"http://qt.nokia.com/\"><span style=\"text-decoration: underline; color: rgb(0, 0, 255);\">qt.nokia.com</span></a> for more information.<!--EndFragment--></p>";
    label->setText(text);  
}

void GmailWidget::setEmailsList(QList< emailStruct > list)
{    
    emailsList = list;
}

void GmailWidget::startTimer(int time)
{
    timer->stop();
    timer->start(time);
}

int GmailWidget::getTopPanel()
{
    int topPanel = 0;
    #ifdef Q_WS_X11
    char * pPath = getenv ("KDE_FULL_SESSION");
    if (QString(pPath) == NULL)
    {
        QProcess gconf;
        gconf.start("gconftool", QStringList() << "--get" <<  "/schemas/apps/panel/toplevels/size");   
        
        gconf.waitForStarted();         
        gconf.closeWriteChannel();
        gconf.waitForFinished();

        QByteArray result = gconf.readAll();
        
        QString str = QString(result);
        int j = 0;
        j = str.indexOf("Default Value:", j);
        
        int k = 0;
        k = str.indexOf("Owner:", k);         
        
        topPanel = str.section("", j, k).trimmed().section("",-3,-1).toInt();
    }
    #endif
    return topPanel;
}

void GmailWidget::getEmailDate(int index)
{
    QDateTime dateTime0 = QDateTime::fromString(emailsList.at(index).issued, "yyyy-MM-ddTHH:mm:ssZ");
    QDateTime dateTime =  QDateTime::fromTime_t(dateTime0.toTime_t()+getTimeZoneOffset().toInt()*3600);
    eDate.year = dateTime.date().year();
    eDate.month = dateTime.date().month();
    eDate.day = dateTime.date().day();
    eDate.hour = dateTime.toLocalTime().time().hour();
    eDate.minute = dateTime.time().minute();
    eDate.second = dateTime.time().second();
    eDate.shortMonth = dateTime.toString("MMM");
}

QString GmailWidget::getTimeZoneOffset()
{
    QDateTime dt1 = QDateTime::currentDateTime();
    QDateTime dt2 = dt1.toUTC();
    dt1.setTimeSpec(Qt::UTC);
    
    int offset = dt2.secsTo(dt1) / 3600;

    if (offset > 0)
        return QString("+%1").arg(offset);
    
    return QString("%1").arg(offset);
}
//
