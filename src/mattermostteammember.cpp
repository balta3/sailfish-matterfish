#include "mattermostteammember.h"

MattermostTeamMember::MattermostTeamMember(QObject *parent) : QObject(parent)
{

}

QString MattermostTeamMember::getUserId() const
{
    return userId;
}

void MattermostTeamMember::setUserId(const QString &value)
{
    userId = value;
}

QString MattermostTeamMember::getChannelId() const
{
    return channelId;
}

void MattermostTeamMember::setChannelId(const QString &value)
{
    channelId = value;
}
