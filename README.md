# QEasySettings
Easy to use manage settings and style options for your Qt projects!

## How to use?
Include the header file named "qeasysettings.hpp" into your qt project then you have to init **QEasySettings** singleton object for how settings are stored in computer.``QEasySettings::init(QEasySettings::Format::regformat, "yourappname")`` is example for init object and store setting in registry under **"yourappname"** key. Other option is **QEasySettings::Format::iniformat** that stores the settings in "yourappname" file. Change themes simply type ``QEasySettings::setStyle(QEasySettings::Style::darkFusion);`` for Fusion Dark style.  
This updated version have an auto follow **Windows 10 dark/light scheme feature** and you can simply write ``QEasySettings::setStyle(QEasySettings::Style::autoFusion);`` to use it!

Other theme/style choices in the table.

| Style | Enum value | 
|---|---|
| AutoFusion | QEasySettings::Style::autoFusion |
| Default | QEasySettings::Style::vista |
| Classic | QEasySettings::Style::classic |
| Fusion Light | QEasySettings::Style::lightFusion |
| Fusion Dark | QEasySettings::Style::darkFusion |

You can read settings with ``QEasySettings::readSettings(QString group, QString key);`` function. This function reads settings.ini file for given QString group and QString key argument. If these group and key found in settings.ini file then function returns key's value in QVariant type.

Load style/theme settings with ``QEasySettings::loadStyle();`` and using this return value then set style/theme options with ``QEasySettings::setStyle(enum QEasySettings::Style retValue);`` function.

You can write settings with ``QEasySettings::writeSettings(QString group, QString key, T option);`` fuction. This function creates settings.ini file and writes group, key and its value (T type option). 

And write styling/theme settings using  ``QEasySettings::writeStyle(enum QEasySettings::Style);``

## Example settings.ini file 
>
> **[Group]**
>
> **Key**=*value*

## Fusion Dark theme screenshots:

![ss1](https://raw.githubusercontent.com/cheytacllc/QtSettingsandTheme/master/2018-09-14_192745.jpg)
![ss2](https://raw.githubusercontent.com/cheytacllc/QtSettingsandTheme/master/2018-09-14_192822.jpg)
