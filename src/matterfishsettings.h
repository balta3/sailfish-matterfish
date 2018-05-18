#ifndef MATTERFISHSETTINGS_H
#define MATTERFISHSETTINGS_H

#include "qmlsettingswrapper.h"

class MatterfishSettings : public QMLSettingsWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
public:
    explicit MatterfishSettings(QObject *parent = 0);

    QString getHost() {return this->value("host").toString();}
    QString getUsername() {return this->value("username").toString();}
    QString getPassword() {return this->value("password").toString();}

    void setHost(QString val) {this->setValue("host", val); emit this->hostChanged(val);}
    void setUsername(QString val) {this->setValue("username", val); emit this->usernameChanged(val);}
    void setPassword(QString val) {this->setValue("password", val); emit this->passwordChanged(val);}

signals:
    void hostChanged(QString);
    void usernameChanged(QString);
    void passwordChanged(QString);
};

#endif // MATTERFISHSETTINGS_H
