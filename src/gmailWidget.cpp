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
    //adjustWindow();
} 

void GmailWidget::showWidget()
{
    width = 362, height = 0, x = 918, y = 776;    
    setGeometry(x,y,width,height);
    repeat = 0;
    show();
    startTimer(90);
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
    move (x, y);
    //setGeometry(x,y,0,0); 
}

void GmailWidget::moveWindow()
{      
    repeat++;
    if (repeat < 7)
    {
        moveUp();
    }
    else if (repeat >= 7 && repeat < 20)
    {
        ;
    }
    else if (repeat >= 20 && repeat < 26)
    {
        moveDown();
    }
    else if (repeat >= 26)
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

void GmailWidget::startTimer(int time)
{
    timer->start(time);
}
//
