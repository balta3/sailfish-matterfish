#ifndef MATTERMOSTTEAM_H
#define MATTERMOSTTEAM_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>

#include "mattermostchannel.h"

class MattermostTeam : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString displayName READ getDisplayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(QQmlListProperty<MattermostChannel> channels READ getChannelsQML NOTIFY channelsChanged)
public:
    explicit MattermostTeam(QObject *parent = nullptr);

    QString getId() const;
    void setId(const QString &value);

    QString getDisplayName() const;
    void setDisplayName(const QString &value);

    QList<MattermostChannel*> getChannels();
    void addChannel(MattermostChannel* channel);
    void clearChannels();
    QQmlListProperty<MattermostChannel> getChannelsQML();

signals:
    void idChanged(const QString &value);
    void displayNameChanged(const QString &value);
    void channelsChanged();

public slots:

private:
    QString id;
    QString displayName;
    QList<MattermostChannel*> channels;
};

#endif // MATTERMOSTTEAM_H
