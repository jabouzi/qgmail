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
}

void GmailImpl::init()
{    
    setGeometry(918,751,362,100);
    adjustWindow();
} 

void GmailImpl::adjustWindow(){       
    windowSize = size();     
    move(rect.width() - windowSize.width(),rect.height() - windowSize.height());    
}
//
