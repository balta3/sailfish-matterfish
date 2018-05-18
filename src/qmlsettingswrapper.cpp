#include "qmlsettingswrapper.h"
#include <QDebug>

QMLSettingsWrapper::QMLSettingsWrapper(QString organisation, QString application, QObject *parent) :
    QObject(parent),
    settings(new QSettings(organisation, application, this))
{
    if (!settings->value("locale").toBool())
        settings->setValue("locale", QLocale().name().mid(0, 2));
}

QVariant QMLSettingsWrapper::value(const QString &key){
    return this->settings->value(key);
}

QVariant QMLSettingsWrapper::value(const QString &key, const QVariant &defaultValue){
    if (this->settings->contains(key)) {
        return this->settings->value(key);
    } else {
        return defaultValue;
    }
}

void QMLSettingsWrapper::setValue(const QString &key, const QVariant &value){
    qDebug() << "set settings value" << key << "->" << value;
    this->settings->setValue(key, value);
}
