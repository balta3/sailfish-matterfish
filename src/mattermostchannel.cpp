#include "mattermostchannel.h"

#include <QJsonObject>
#include <QJsonArray>

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
    connect(value, SIGNAL(lastViewedChanged(QDateTime)), this, SLOT(memberLastViewedChanged(QDateTime)));
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

void MattermostChannel::addPost(MattermostPost *post, bool emitSignal)
{
    if (this->posts.isEmpty()) {
        this->posts << post;
    } else {
        QList<MattermostPost*>::iterator end = this->posts.end();
        QList<MattermostPost*>::iterator p = this->posts.begin();
        while (p != end && (((MattermostPost*)*p)->getCreated() < post->getCreated())) {
            p++;
        }
        this->posts.insert(p, post);
    }
    if (emitSignal) {
        emit this->postsChanged();
    }
    if (this->lastPostAt < post->getCreated()) {
        this->setLastPostAt(post->getCreated());
    }
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

void MattermostChannel::updatePosts(QJsonDocument& doc, QMap<QString, MattermostUser*> users) {
    this->clearPosts();
    QJsonObject container = doc.object();
    QJsonArray orderArray = container["order"].toArray();
    QJsonObject posts = container["posts"].toObject();
    foreach (const QJsonValue &orderJson, orderArray) {
        QString postId = orderJson.toString();
        QJsonObject postJson = posts[postId].toObject();
        this->addPost(postJson, users, false);
    }
    emit this->postsChanged();
}

MattermostFile *MattermostChannel::findFileById(QString fileId)
{
    foreach (MattermostPost* post, this->posts) {
        foreach (MattermostFile* file, post->getFiles()) {
            if (file->getId() == fileId) {
                return file;
            }
        }
    }
    return 0;
}

void MattermostChannel::memberLastViewedChanged(const QDateTime &value)
{
    Q_UNUSED(value)
    emit this->unreadChanged(this->isUnread());
}

void MattermostChannel::addPost(QJsonObject &postJson, QMap<QString, MattermostUser*> users, bool emitSignal) {
    MattermostUser* user = users[postJson["user_id"].toString()];
    MattermostPost* post = new MattermostPost(user, postJson, this);
    this->addPost(post, emitSignal);
}
