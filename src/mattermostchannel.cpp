#include "mattermostchannel.h"

MattermostChannel::MattermostChannel(QObject *parent) : QObject(parent)
{
    this->member = 0;
    this->totalMsgCount = 0;
}

QString MattermostChannel::getId() const
{
    return id;
}

void MattermostChannel::setId(const QString &value)
{
    id = value;
}

QString MattermostChannel::getType() const
{
    return type;
}

void MattermostChannel::setType(const QString &value)
{
    type = value;
}

QString MattermostChannel::getDisplayName() const
{
    return displayName;
}

void MattermostChannel::setDisplayName(const QString &value)
{
    displayName = value;
}

QDateTime MattermostChannel::getLastUpdated() const
{
    return lastUpdated;
}

void MattermostChannel::setLastUpdated(const QDateTime &value)
{
    lastUpdated = value;
}

MattermostTeamMember *MattermostChannel::getMember() const
{
    return member;
}

void MattermostChannel::setMember(MattermostTeamMember *value)
{
    member = value;
    emit this->memberChanged(*this->member);
    emit this->unreadChanged(this->isUnread());
}

bool MattermostChannel::isUnread()
{
    if (!this->member) {
        return false;
    }
    return this->totalMsgCount > 0 && this->lastPostAt > this->member->getLastViewed();
}

uint MattermostChannel::getTotalMsgCount() const
{
    return totalMsgCount;
}

void MattermostChannel::setTotalMsgCount(const uint &value)
{
    totalMsgCount = value;
    emit this->totalMsgCountChanged(this->totalMsgCount);
    emit this->unreadChanged(this->isUnread());
}

QDateTime MattermostChannel::getLastPostAt() const
{
    return lastPostAt;
}

void MattermostChannel::setLastPostAt(const QDateTime &value)
{
    lastPostAt = value;
    emit this->lastPostAtChanged(this->lastPostAt);
    emit this->unreadChanged(this->isUnread());
}

QList<MattermostPost *> MattermostChannel::getPosts() const
{
    return posts;
}

void MattermostChannel::setPosts(const QList<MattermostPost *> &value)
{
    posts = value;
}

void MattermostChannel::addPost(MattermostPost *post)
{
    this->posts.prepend(post);
    emit this->postsChanged();
}

void MattermostChannel::clearPosts()
{
    this->posts.clear();
    emit this->postsChanged();
}

QQmlListProperty<MattermostPost> MattermostChannel::getPostsQML()
{
    return QQmlListProperty<MattermostPost>(this, this->posts);
}

QString MattermostChannel::getName() const
{
    return name;
}

void MattermostChannel::setName(const QString &value)
{
    name = value;
}
