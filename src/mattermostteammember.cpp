#include "mattermostteammember.h"

MattermostTeamMember::MattermostTeamMember(QObject *parent) : QObject(parent)
{
    this->lastUpdated = QDateTime::currentDateTime();
    this->lastUpdated.setTime_t(0);
    this->lastViewed = QDateTime::currentDateTime();
    this->lastViewed.setTime_t(0);
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

QDateTime MattermostTeamMember::getLastViewed() const
{
    return lastViewed;
}

void MattermostTeamMember::setLastViewed(const QDateTime &value)
{
    lastViewed = value;
    emit this->lastViewedChanged(this->lastViewed);
    emit this->unreadChanged(this->isUnread());
}

QDateTime MattermostTeamMember::getLastUpdated() const
{
    return lastUpdated;
}

void MattermostTeamMember::setLastUpdated(const QDateTime &value)
{
    lastUpdated = value;
    emit this->lastUpdatedChanged(this->lastUpdated);
    emit this->unreadChanged(this->isUnread());
}

bool MattermostTeamMember::isUnread()
{
    return this->msgCount > 0 && this->lastUpdated > this->lastViewed;
}

quint16 MattermostTeamMember::getMsgCount() const
{
    return msgCount;
}

void MattermostTeamMember::setMsgCount(const quint16 &value)
{
    msgCount = value;
}
