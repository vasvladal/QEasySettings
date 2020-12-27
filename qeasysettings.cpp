/*****************************************************************************
 * qeasysettings.cpp
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
#include "qeasysettings.hpp"
#include <QStyle>
#include <QStyleFactory>
#include <QToolTip>
#include <QApplication>
#include <QDesktopWidget>
#include <QPalette>
#include <QTimer>

QEasySettings *QEasySettings::m_instance = nullptr;
bool QEasySettings::m_autoPalette=false;
bool QEasySettings::m_islight;
QPalette QEasySettings::mPalette;
QSettings QEasySettings::m_settings{"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",QSettings::NativeFormat};
QTimer QEasySettings::mTimer;


void QEasySettings::init(QEasySettings::Format format, const QString &name)
{
    if (!m_instance){
        m_instance = new QEasySettings(format, name);
        sConnectionCallback(*m_instance);
    }
}

QEasySettings::~QEasySettings()
{
    delete m_instance;
    delete m_settingsObj;
}

QEasySettings::Theme QEasySettings::loadStyle()
{
    int val;
    m_instance->m_settingsObj->beginGroup("Style");
    val = m_instance->m_settingsObj
            ->value("Theme", static_cast<int>(Theme::lightFusion))
            .toInt(); // default theme is lightFusion
    m_instance->m_settingsObj->endGroup();
    return static_cast<Theme>(val);
}

void QEasySettings::setStyle(const QEasySettings::Theme val)
{
    switch (val) {
    case Theme::autoFusion:
        qApp->setStyle(QStyleFactory::create("Fusion"));
        setAutoPalette(true);
        break;
    case Theme::vista:
        qApp->setStyle(QStyleFactory::create("windowsvista"));
        setAutoPalette(false);
        changePalette(Palette::light);
        break;
    case Theme::classic:
        qApp->setStyle(QStyleFactory::create("windows"));
        setAutoPalette(false);
        changePalette(Palette::light);
        break;
    case Theme::lightFusion:
        qApp->setStyle(QStyleFactory::create("Fusion"));
        setAutoPalette(false);
        changePalette(Palette::light);
        break;
    case Theme::darkFusion:
        qApp->setStyle(QStyleFactory::create("Fusion"));
        setAutoPalette(false);
        changePalette(Palette::dark);
        break;
    default:
        break;
    }
}

QVariant QEasySettings::readSettings(const QString group, const QString key)
{
    QVariant val;
    m_instance->m_settingsObj->beginGroup(group);
    val = m_instance->m_settingsObj->value(key);
    m_instance->m_settingsObj->endGroup();
    return val;
}

void QEasySettings::writeStyle(const QEasySettings::Theme &option){
    m_instance->m_settingsObj->beginGroup("Style");
    m_instance->m_settingsObj->setValue("Theme", static_cast<int>(option));
    m_instance->m_settingsObj->endGroup();
}

QEasySettings::QEasySettings(QEasySettings::Format format, const QString &name)
{
    (static_cast<bool>(format))
            ? m_settingsObj = new QSettings(name, QSettings::IniFormat)
            : m_settingsObj = new QSettings(name, QApplication::applicationName());
}

void QEasySettings::setAutoPalette(bool autoPalette)
{
    m_autoPalette = autoPalette;
    setupEventLoop(autoPalette);
}

void QEasySettings::changePalette(QEasySettings::Palette _palette)
{
    if (static_cast<bool>(_palette)) {
        mPalette = qApp->style()->standardPalette();
    } else{
        mPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        mPalette.setColor(QPalette::WindowText, Qt::white);
        mPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        mPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        mPalette.setColor(QPalette::ToolTipBase, QColor(53, 53, 53));
        mPalette.setColor(QPalette::ToolTipText, Qt::white);
        mPalette.setColor(QPalette::Text, Qt::white);
        mPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        mPalette.setColor(QPalette::ButtonText, Qt::white);
        mPalette.setColor(QPalette::BrightText, Qt::red);
        mPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        mPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        mPalette.setColor(QPalette::HighlightedText, Qt::black);
        mPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(164, 166, 168));
        mPalette.setColor(QPalette::Disabled, QPalette::WindowText,
                          QColor(164, 166, 168));
        mPalette.setColor(QPalette::Disabled, QPalette::ButtonText,
                          QColor(164, 166, 168));
        mPalette.setColor(QPalette::Disabled, QPalette::HighlightedText,
                          QColor(164, 166, 168));
        mPalette.setColor(QPalette::Disabled, QPalette::Base, QColor(68, 68, 68));
        mPalette.setColor(QPalette::Disabled, QPalette::Window, QColor(68, 68, 68));
        mPalette.setColor(QPalette::Disabled, QPalette::Highlight,
                          QColor(68, 68, 68));
    }

    QToolTip::setPalette(mPalette);
    qApp->setPalette(mPalette);
}

void QEasySettings::sConnectionCallback(QEasySettings &s)
{
    connect(&s,SIGNAL(notifyPalette(bool)),&s,SLOT(bool2PaletteHelper(bool)), Qt::QueuedConnection);
    connect(&mTimer,&QTimer::timeout,&s,&QEasySettings::eventLoop);
    mTimer.setInterval(100);
}

void QEasySettings::bool2PaletteHelper(bool b)
{
    changePalette(static_cast<enum Palette>(b));
}

void QEasySettings::setupEventLoop(const bool &event)
{
    m_autoPalette=event;
    event ? mTimer.start() : mTimer.stop();
}

void QEasySettings::eventLoop()
{
    if (m_autoPalette) {
        auto const temp = m_settings.value("AppsUseLightTheme",true).toBool();
        if(temp==m_islight) sigHandler(temp, *m_instance);
        m_islight=temp;
    }
}

void QEasySettings::sigHandler(bool b, const QEasySettings &s)
{
    s.notifyPalette(b);
}
