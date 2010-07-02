#include "gmailImpl.h"
//
GmailImpl::GmailImpl( QWidget * parent) 
    : QWidget(parent)
{
    setupUi(this);
    desktop = QApplication::desktop();
    rect = desktop->availableGeometry(0);   
    opac = 0.9;
    this->setWindowOpacity(opac);     
    QImage image("images/gmail4.png");    
    label_3->setPixmap(QPixmap::fromImage(image));       
    repeat = 0;  
    timer = new QTimer(this);    
    connect(timer, SIGNAL(timeout()), this, SLOT(moveWindow()));      
}

void GmailImpl::init()
{    
    //setGeometry(918,751,362,66);    
    adjustWindow();
} 

void GmailImpl::show_()
{
    show();
    startTimer(100);
}

void GmailImpl::adjustWindow(){       
    //~ windowSize = size();     
    //~ move(rect.width() - windowSize.width(),rect.height() - windowSize.height());    
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rec1 = desktop->availableGeometry (0);
    QRect rec2 = desktop->screenGeometry (0);     
    int screenWidth, width; 
    int screenHeight, height;    
    QSize windowSize;     
    screenWidth = desktop->width(); 
    screenHeight = desktop->height();
    qDebug("Screen  => H : %d, W : %d",screenWidth,screenHeight);   
    windowSize = size(); 
    width = windowSize.width(); 
    height = windowSize.height(); 
    qDebug("Widget => H : %d, W : %d",width,height);   
    qDebug("Rec1 => H : %d, W : %d",rec1.width() ,rec1.height() );  
    qDebug("Rec2 => H : %d, W : %d",rec2.width() ,rec2.height() );  
    x = (screenWidth - width);
    y = (screenHeight - height);
    qDebug("XY => H : %d, W : %d",x ,y );
    int diff1 = rec2.height() - rec1.height();
    int diff2 = rec2.width() - rec1.width();  
    qDebug("diff => H : %d, W : %d",diff1 ,diff2 );  
    qDebug("H : %d, W : %d",x+diff2 ,y+diff1);  
    move (screenWidth, screenHeight);
}

void GmailImpl::moveWindow()
{
    y = y - 10;
    move (x, y);
    repeat++;
    qDebug("Repeat : %d ",repeat);
    startTimer(100);
    if (repeat >= 6)
    {        
        timer->stop();
    }
    
    /* if (repeat < 6)
    {
        y = y + 10;
        move (x, y);
        repeat++;
        startTimer(100);
    }
    else if (repeat == 7)
    {
        repeat++;
        startTimer(2000);        
    }
    else if (repeat > 7 and repeat < 13)
    {
        y = y + 10;
        move (x, y);
        repeat++;
        startTimer(100);
    }*/
}

void GmailImpl::startTimer(int time)
{    
    timer->start(time);
}
//
