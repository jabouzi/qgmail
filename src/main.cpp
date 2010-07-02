#include <QApplication>
#include "gmail.h"
//
int main(int argc, char ** argv)
{
	QApplication app( argc, argv );
	Gmail win;
	win.hide(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();
}
