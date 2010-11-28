#include <QApplication>
#include "qtgmail.h"
//
int main(int argc, char ** argv)
{
    QApplication app( argc, argv );
    QApplication::setApplicationName("qtgmail");
    QtGmail win;
    win.hide(); 
    app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
    return app.exec();
}
