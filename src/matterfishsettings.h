#ifndef MATTERFISHSETTINGS_H
#define MATTERFISHSETTINGS_H

#include "qmlsettingswrapper.h"

class MatterfishSettings : public QMLSettingsWrapper
{
    Q_OBJECT
    Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(bool onlineInBackground READ isOnlineInBackground WRITE setOnlineInBackground NOTIFY onlineInBackgroundChanged)
public:
    explicit MatterfishSettings(QObject *parent = 0);

    QString getHost() {return this->value("host").toString();}
    QString getUsername() {return this->value("username").toString();}
    QString getPassword() {return this->value("password").toString();}
    bool isOnlineInBackground() {return this->value("onlineInBackground").toBool();}

    void setHost(QString val) {this->setValue("host", val); emit this->hostChanged(val);}
    void setUsername(QString val) {this->setValue("username", val); emit this->usernameChanged(val);}
    void setPassword(QString val) {this->setValue("password", val); emit this->passwordChanged(val);}
    void setOnlineInBackground(bool val) {this->setValue("onlineInBackground", val); emit this->onlineInBackgroundChanged(val);}

signals:
    void hostChanged(QString);
    void usernameChanged(QString);
    void passwordChanged(QString);
    void onlineInBackgroundChanged(bool);
};

#endif // MATTERFISHSETTINGS_H
