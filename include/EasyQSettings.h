

#ifndef EASYQSETTINGS_H
#define EASYQSETTINGS_H

#include <QSettings>
#include <QDebug>
#include <QCoreApplication>
#include <QMutex>

// Abstract base class
class SettingsBase
{
public:
	virtual ~SettingsBase() = default;
	virtual void SaveSettings() = 0;
	virtual void LoadSettings() = 0;
};

class EasyQSettings
{
private:
	QSettings settings_;
	QMutex	  mutex_;

protected:
	EasyQSettings(const QString& filePath) : settings_(filePath, QSettings::IniFormat)
	{
		qInfo() << "EasyQSettings initialized with file:" << filePath;
	}

	// delete copy constructor and assignment operator
	EasyQSettings(const EasyQSettings&) = delete;
	EasyQSettings& operator=(const EasyQSettings&) = delete;

public:
	static EasyQSettings& getInstance(const QString& filePath)
	{
		static EasyQSettings instance(filePath);
		return instance;
	}
	bool SaveVal(const QString& group, const QString& key, const QVariant& value)
	{
		QMutexLocker locker(&mutex_); // Lock the mutex_

		bool status = false;

		settings_.beginGroup(group);
		settings_.setValue(key, value);

		if (settings_.status() == QSettings::NoError)
		{
			status = true;
		}
		else
		{
			qCritical() << "Error in saving";
		}

		settings_.endGroup();
		qInfo() << Q_FUNC_INFO << settings_.status();

		return status;
	}

	QVariant LoadVal(const QString& group, const QString& key, const QVariant& defaultValue)
	{
		QMutexLocker locker(&mutex_); // Lock the mutex_

		QVariant value;
		settings_.beginGroup(group);

		if (!settings_.contains(key))
		{
			qWarning() << "Key" << key << "not found";
			settings_.endGroup();
			return defaultValue;
		}

		value = settings_.value(key, defaultValue);

		if (settings_.status() != QSettings::NoError)
		{
			qCritical() << "Error in loading";
		}

		settings_.endGroup();
		qInfo() << Q_FUNC_INFO << settings_.status();

		return value;
	}

	// for debugging purposes
	void DisplaySettings()
	{
		foreach (const QString& group, settings_.childGroups())
		{
			qInfo() << "Group:" << group;
			settings_.beginGroup(group);
			foreach (const QString& key, settings_.childKeys())
			{
				qInfo() << "__ Key:" << key;
				qInfo() << "_____ Value:" << settings_.value(key).toString();
			}
			settings_.endGroup();
		}
	}
};



#endif // EASYQSETTINGS_H
