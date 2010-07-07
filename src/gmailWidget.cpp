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

void GmailWidget::init(QString path)
{    
    this->setWindowOpacity(opac);
    QImage image(path+"images/gmail4.png");
    label_3->setPixmap(QPixmap::fromImage(image));
    label->setTextFormat(Qt::RichText);
    //adjustWindow();
} 

void GmailWidget::showWidget()
{
    setMessage(0);      
    windowSize = size();      
    width = windowSize.width(); 
    height = windowSize.height(); 
    QRect rec1 = desktop->screenGeometry (0);    
    height = 0, x = rec1.width() - width, y = rec1.height() - 24;    
    setGeometry(x,y,width,height);
    repeat = 0;
    show();
    startTimer(90);
    emailIndex = 1;
}

void GmailWidget::adjustWindow(){    
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rec1 = desktop->availableGeometry (0);
    QRect rec2 = desktop->screenGeometry (0);         
    screenWidth = desktop->width(); 
    screenHeight = desktop->height();
    qDebug("Screen  => W : %d, H : %d",screenWidth,screenHeight);  
    windowSize = size();      
    width = windowSize.width(); 
    height = windowSize.height(); 
    qDebug("Widget => W : %d, H : %d",width,height);   
    qDebug("Rec1 => W : %d, H : %d",rec1.width() ,rec1.height() );  
    qDebug("Rec2 => W : %d, H : %d",rec2.width() ,rec2.height() );  
    x = (screenWidth - width);
    y = (screenHeight - height);
    qDebug("XY => W : %d, H : %d",x ,y );
    int diff1 = rec2.height() - rec1.height();
    int diff2 = rec2.width() - rec1.width();  
    qDebug("diff => H : %d, W : %d",diff1 ,diff2 );  
    qDebug("H : %d, W : %d",x+diff2 ,y+diff1);  
    x = 918;
    y = 710;
    //move (x, y);
    //setGeometry(x,y,0,0); 
}

void GmailWidget::moveWindow()
{      
    repeat++;   
    //qDebug("repeat : %d",repeat); 
    if (repeat < 7)
    {
        moveUp();
    }
    else if (repeat >= 8 && repeat < 9)
    {
        timer->stop();
        timer2->start(5000);        
    }
    else if (repeat >= 9 && repeat < 15)
    {
        moveDown();
    }
    else if (repeat >= 15)
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
        //qDebug("emailIndex : %d",emailIndex);    
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

void GmailWidget::setEmailsList(QList< emailStruct > list)
{    
    emailsList = list;
}

void GmailWidget::startTimer(int time)
{
    timer->stop();
    timer->start(time);
}

void GmailWidget::getEmailDate(int index)
{
    QDateTime dateTime0 = QDateTime::fromString(emailsList.at(index).issued, "yyyy-MM-ddTHH:mm:ssZ");
    //~ int tz = getTimeZoneOffset();
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


//Your inbox contains no unread conversations.
