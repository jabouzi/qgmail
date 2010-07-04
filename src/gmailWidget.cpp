#include "gmailWidget.h"
//
GmailWidget::GmailWidget( QWidget * parent) 
    : QWidget(parent)
{
    setupUi(this);
    desktop = QApplication::desktop();
    rect = desktop->availableGeometry(0);
    opac = 0.9;    
    repeat = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveWindow()));
}

void GmailWidget::init(QString path)
{
    this->setWindowOpacity(opac);
    QImage image(path+"images/gmail4.png");
    label_3->setPixmap(QPixmap::fromImage(image));
    adjustWindow();
} 

void GmailWidget::showWidget()
{
    repeat = 0;
    show();
    startTimer(80);
}

void GmailWidget::adjustWindow(){    
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rec1 = desktop->availableGeometry (0);
    QRect rec2 = desktop->screenGeometry (0);         
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

void GmailWidget::moveWindow()
{
    repeat++;
    qDebug("Repeat : %d ",repeat);    
    if (repeat < 7)
    {
        moveUp();
    }
    else if (repeat >= 7 && repeat < 15)
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
    y = y - 10;
    height = height + 10;
    setGeometry(x,y,width,height);   
    startTimer(80);    
}

void GmailWidget::moveDown()
{
    y = y + 10;
    height = height - 10;
    setGeometry(x,y,width,height);
    startTimer(80);
}

void GmailWidget::startTimer(int time)
{
    timer->start(time);
}
//
