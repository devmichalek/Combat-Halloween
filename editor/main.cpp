#include <QtWidgets/QApplication>
#include <qfontdatabase.h>
#include "loggingwindow.h"
#include "buttonfactory.h"
#include "logging.h"

int main(int argc, char *argv[])
{
	// App.
	QApplication application(argc, argv);

	// Add font.
	int id = QFontDatabase::addApplicationFont("fonts/Jaapokki-Regular.otf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont font(family);
	QApplication::setFont(font);

	// Create window.
	LoggingWindow* window = new LoggingWindow;

	Logging logging;
	logging.load(window->size());
	logging.setWindowAsParent(window);

	// Buttons.
	// ButtonFactory buttonFactory;
	// buttonFactory.load(window->size());
	// buttonFactory.setParent(window);
	// buttonFactory.setEnabledAll(false);
	// QObject::connect(&logging, SIGNAL(&Logging::isReady()), &buttonFactory, SLOT(&ButtonFactory::setEnabledAll(true)));

	window->show();
	return application.exec();
}
