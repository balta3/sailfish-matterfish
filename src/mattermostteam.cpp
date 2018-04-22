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

void MattermostTeam::clearMembers()
{
    this->members.clear();
    emit this->channelsChanged();
}

void MattermostTeam::addMember(MattermostTeamMember *member)
{
    this->members.append(member);
    emit this->channelsChanged();
}

MattermostTeamMember *MattermostTeam::getMemberByDirectMessageChannelId(QString channelId)
{
    MattermostTeamMember* member = *std::find_if(this->members.begin(), this->members.end(), [channelId] (MattermostTeamMember* m) {return m->getChannelId() == channelId; });
    return member;
}

quint16 MattermostTeam::getMessageCount() const
{
    return messageCount;
}

void MattermostTeam::setMessageCount(quint16 value)
{
    messageCount = value;
    emit this->messageCountChanged(this->messageCount);
}

quint16 MattermostTeam::getMentionCount() const
{
    return mentionCount;
}

void MattermostTeam::setMentionCount(quint16 value)
{
    mentionCount = value;
    emit this->mentionCountChanged(this->mentionCount);
}

QQmlListProperty<MattermostChannel> MattermostTeam::getChannelsQML() {
    return QQmlListProperty<MattermostChannel>(this, this->channels);
}
