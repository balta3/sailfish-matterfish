#include "mattermostteam.h"

#include <algorithm>

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
    this->sortChannels();
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
    return *std::find_if(this->members.begin(), this->members.end(), [channelId] (MattermostTeamMember* m) {return m->getChannelId() == channelId; });
}

MattermostChannel *MattermostTeam::findChannelById(QString channelId)
{
    QList<MattermostChannel*>::iterator channelIt = std::find_if(channels.begin(), channels.end(), [channelId] (MattermostChannel* c) {return c->getId() == channelId;});
    if (*channelIt && channelIt != channels.end()) {
        return *channelIt;
    }
    return 0;
}

MattermostFile *MattermostTeam::findFileById(QString fileId)
{
    foreach (MattermostChannel* channel, this->channels) {
        MattermostFile *file = channel->findFileById(fileId);
        if (file) {
            return file;
        }
    }
    return 0;
}

void MattermostTeam::sortChannels()
{
    QStringList typeOrder;
    typeOrder << "O" << "P" << "D" << "G";
    std::sort(this->channels.begin(), this->channels.end(), [typeOrder](MattermostChannel* a, MattermostChannel* b) -> bool {
        if (a->getType() == b->getType()) {
            return a->getDisplayName() < b->getDisplayName();
        } else {
            return typeOrder.indexOf(a->getType()) < typeOrder.indexOf(b->getType());
        }
    });
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
