#include "mattermostteam.h"

MattermostTeam::MattermostTeam(QObject *parent) : QObject(parent)
{

}

QString MattermostTeam::getId() const
{
    return id;
}

void MattermostTeam::setId(const QString &value)
{
    id = value;
}

QString MattermostTeam::getDisplayName() const
{
    return displayName;
}

void MattermostTeam::setDisplayName(const QString &value)
{
    displayName = value;
}

QList<MattermostChannel *> MattermostTeam::getChannels()
{
    return this->channels;
}

void MattermostTeam::addChannel(MattermostChannel *channel)
{
    this->channels.append(channel);
    emit this->channelsChanged();
}

void MattermostTeam::clearChannels()
{
    this->channels.clear();
    emit this->channelsChanged();
}

QQmlListProperty<MattermostChannel> MattermostTeam::getChannelsQML() {
    return QQmlListProperty<MattermostChannel>(this, this->channels);
}
