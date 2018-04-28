#include "mattermostpost.h"

MattermostPost::MattermostPost(QObject *parent) : QObject(parent)
{

}

QString MattermostPost::getMessage() const
{
    return message;
}

void MattermostPost::setMessage(const QString &value)
{
    message = value;
}

QDateTime MattermostPost::getCreated() const
{
    return created;
}

void MattermostPost::setCreated(const QDateTime &value)
{
    created = value;
}

MattermostUser *MattermostPost::getUser() const
{
    return user;
}

void MattermostPost::setUser(MattermostUser *value)
{
    user = value;
}
