# EasyQSettings

EasyQSettings is a library that provides an easy-to-use wrapper around QSettings, allowing users to quickly implement settings storage and retrieval in their Qt applications.

## Overview

The library is designed to simplify the process of managing application settings using QSettings. It offers thread-safe methods for saving and loading settings, along with a singleton pattern to ensure a single instance of the settings manager.

## Features

- Thread-safe access to settings
- Singleton pattern to ensure a single instance
- Simple API for saving and loading settings
- Customizable implementation through inheritance

## Folder Structure

```
.
├───demo
│       CMakeLists.txt
│       CustomSettings.cpp
│       CustomSettings.h
│       main.cpp
│
└───include
        EasyQSettings.h
        CMakeLists.txt
CMakeLists.txt
```

## demo instructions

1. Clone the repository:
    ```sh
    git clone <repository_url>
    ```

2. Build the project using CMake:
    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

## Usage

### Creating the Settings Manager

Create a custom settings class that inherits from `SettingsBase` and implements the `SaveSettings` and `LoadSettings` methods.

```cpp
#include "CustomSettings.h"

CustomSettings::CustomSettings(const QString& filePath)
    : filePath_(filePath), customSettings_(Settings::getInstance(filePath))
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
    qint32  size1 = customSettings_.LoadVal("Group1", "Font_Size", 10).toInt();
    QString Color2 = customSettings_.LoadVal("Group2", "Font_Color", "White").toString();
    qint32  size2 = customSettings_.LoadVal("Group2", "Font_Size", 10).toInt();

    qInfo() << Q_FUNC_INFO;
}
```

### Using the Settings Manager

```cpp
#include <QCoreApplication>
#include "CustomSettings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString settingsFilePath = "settings.ini";
    CustomSettings settingsManager(settingsFilePath);

    // Save settings
    settingsManager.SaveSettings();

    // Load settings
    settingsManager.LoadSettings();

    return a.exec();
}
```

### CMake Configuration

In your CMakeLists.txt file, add the following configuration:

```cmake
# Add the include directory for the EasyQSettings library
add_subdirectory(EasyQSettings/include)

# Include directories
include_directories(EasyQSettings/include)

# Link the EasyQSettings library
target_link_libraries(${PROJECT_NAME} EasyQSettings)

```


## API Reference

### `Settings` Class

#### Methods

- `static Settings& getInstance(const QString& filePath)`: Returns the singleton instance of the Settings class.
- `bool SaveVal(const QString& group, const QString& key, const QVariant& value)`: Saves a value in the settings file.
- `QVariant LoadVal(const QString& group, const QString& key, const QVariant& defaultValue = QVariant{})`: Loads a value from the settings file.
- `void DisplaySettings()`: Displays all the settings stored in the file. (For debugging purposes)

### `SettingsBase` Class (Abstract)
SettingsBase is an abstract class that provides a base implementation for managing settings. Users can create custom settings classes by inheriting from SettingsBase and implementing the SaveSettings and LoadSettings methods.

#### Methods

- `virtual void SaveSettings() = 0`: Pure virtual method to save settings. Must be implemented by the derived class.
- `virtual void LoadSettings() = 0`: Pure virtual method to load settings. Must be implemented by the derived class.

## License

This library is licensed under the MIT License. Feel free to use it in your projects.