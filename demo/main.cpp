#include <QCoreApplication>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include "CustomSettings.h"
#include "EasyQSettings.h" // for DisplaySettings() function it should be included

#include <QThreadPool>

// Function to save settings in a separate thread
void saveSettings(const QString& filePath)
{
	CustomSettings customSettings(filePath);
	customSettings.SaveSettings();

	qInfo() << Q_FUNC_INFO << QThread::currentThreadId();
}
// Function to load settings in a separate thread
void loadSettings(const QString& filePath)
{
	CustomSettings customSettings(filePath);
	customSettings.LoadSettings();

	qInfo() << Q_FUNC_INFO << QThread::currentThreadId();
}

void printSettings(const QString& filePath)
{
	EasyQSettings::getInstance(filePath).DisplaySettings();
}

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);

	// Display the thread ID
	qInfo() << "Main thread ID: " << QThread::currentThreadId();

	QCoreApplication::setOrganizationName("ITIDA");
	QCoreApplication::setApplicationName("MyApp");

	QString filePath =
		QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName() + ".ini";

	QFuture<void> saveFuture = QtConcurrent::run(saveSettings, filePath);

	saveFuture.waitForFinished();

	QFuture<void> loadFuture = QtConcurrent::run(loadSettings, filePath);

	loadFuture.waitForFinished();

	printSettings(filePath);

	qInfo() << "Main thread finished ID: " << QThread::currentThreadId();
	return a.exec();
}
