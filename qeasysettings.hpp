/*****************************************************************************
 * qeasysettings.hpp
 *
 * Created: 12/27/2020 2020 by mguludag
 *
 * Copyright 2020 mguludag. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#ifndef QEASYSETTINGS_HPP
#define QEASYSETTINGS_HPP

#include <QSettings>

class QPalette;
class QTimer;


class QEasySettings : public QObject
{
    Q_OBJECT
public:
    enum class Style { autoFusion, vista, classic, lightFusion, darkFusion };
    enum class Format { regFormat, iniFormat };

    static void init(Format format, const QString &name);
    ~QEasySettings();
    /*!
    \fn int loadStyle
    \brief Loads current application style from settings file or registry
    */
    static Style loadStyle();
    /*!
    \fn void setStyle
    \brief Apply a given style to application
    */
    static void setStyle(const Style val);
    /*!
    \fn QVariant readSettings
    \brief Read a value stored in settings given group and key
    */
    static QVariant readSettings(const QString group, const QString key);
    template <typename T>
    /*!
    \fn void writeSettings
    \brief Write a value in settings given group and key
    */
    static void writeSettings(const QString group, const QString key,
                              const T &option)
    {
        m_instance->m_settingsObj->beginGroup(group);
        m_instance->m_settingsObj->setValue(key, option);
        m_instance->m_settingsObj->endGroup();
    }

    static void writeStyle(const enum Style &option);

private:
    enum class Palette { dark, light };
    static QEasySettings *m_instance;
    QSettings *m_settingsObj = nullptr;
    static QPalette mPalette;
    static bool m_autoPalette;
    static QSettings m_settings;
    static QTimer mTimer;
    static bool m_islight;

    QEasySettings() = delete;
    QEasySettings(Format format, const QString &name);
    static void setAutoPalette(bool autoPalette);
    static void changePalette(enum Palette _palette);
    static void sConnectionCallback(QEasySettings &s);

signals:
    void notifyPalette(bool) const;
    void startEvent();

private slots:
    static void bool2PaletteHelper(bool b);
    static void setupEventLoop(const bool &event);
    static void eventLoop();
    static void sigHandler(bool b, const QEasySettings &s);
};

#endif // QEASYSETTINGS_HPP
