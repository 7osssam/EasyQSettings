#include <QCoreApplication>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include "CustomSettings.h"
#include "EasyQSettings.h" // for DisplaySettings() function it should be included

#include <QThreadPool>

// Function to save settings in a separate thread
void saveSettings()
{
	CustomSettings &customSettings = CustomSettings::getInstance();

	customSettings.SaveSettings();

	qInfo() << Q_FUNC_INFO << QThread::currentThreadId();
}
// Function to load settings in a separate thread
void loadSettings()
{
	CustomSettings &customSettings = CustomSettings::getInstance();
	customSettings.LoadSettings();

	qInfo() << Q_FUNC_INFO << QThread::currentThreadId();
}

// for debugging purposes only
void printSettings(const QString &filePath)
{
	EasyQSettings::getInstance(filePath).DisplaySettings();
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// Display the thread ID
	qInfo() << "Main thread ID: " << QThread::currentThreadId();

	QCoreApplication::setOrganizationName("ITIDA");
	QCoreApplication::setApplicationName("MyApp");

	QFuture<void> saveFuture = QtConcurrent::run(saveSettings);

	saveFuture.waitForFinished();

	QFuture<void> loadFuture = QtConcurrent::run(loadSettings);

	loadFuture.waitForFinished();

	printSettings(QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName() + ".ini");

	qInfo() << "Main thread finished ID: " << QThread::currentThreadId();
	return a.exec();
}
