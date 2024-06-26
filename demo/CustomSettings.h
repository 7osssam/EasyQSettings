#ifndef CUSTOMSETTINGS_H
#define CUSTOMSETTINGS_H

#include "EasyQSettings.h"

class CustomSettings : public SettingsBase
{
private:
	EasyQSettings &customSettings_;
	const QString filePath_;

	// singleton
	CustomSettings();

	CustomSettings(const CustomSettings &) = delete;
	CustomSettings &operator=(const CustomSettings &) = delete;

public:
	static CustomSettings &getInstance();

	void SaveSettings() override;
	void LoadSettings() override;
};

#endif // CUSTOMSETTINGS_H
