#include "CustomSettings.h"

CustomSettings::CustomSettings(const QString& filePath) :
	filePath_(filePath), customSettings_(EasyQSettings::getInstance(filePath))
{
	qInfo() << "CustomSettings initialized with file:" << filePath;
}

void CustomSettings::SaveSettings()
{
	customSettings_.SaveVal("Group1", "Font_Color", "Black");
	customSettings_.SaveVal("Group1", "Font_Size", 20);
	customSettings_.SaveVal("Group2", "Font_Color", "Yellow");
	customSettings_.SaveVal("Group2", "Font_Size", 34);

	qInfo() << Q_FUNC_INFO;
}

void CustomSettings::LoadSettings()
{
	QString Color1 = customSettings_.LoadVal("Group1", "Font_Color", "White").toString();
	qint32	size1 = customSettings_.LoadVal("Group1", "Font_Size", 10).toInt();
	QString Color2 = customSettings_.LoadVal("Group2", "Font_Color", "White").toString();
	qint32	size2 = customSettings_.LoadVal("Group2", "Font_Size", 10).toInt();

	qInfo() << Q_FUNC_INFO;
}
