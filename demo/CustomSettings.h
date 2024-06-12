#ifndef CUSTOMSETTINGS_H
#define CUSTOMSETTINGS_H

#include "EasyQSettings.h"

class CustomSettings : public SettingsBase
{
private:
	EasyQSettings& customSettings_;
	const QString  filePath_;

public:
	CustomSettings(const QString& filePath);

	void SaveSettings() override;
	void LoadSettings() override;
};

#endif // CUSTOMSETTINGS_H
