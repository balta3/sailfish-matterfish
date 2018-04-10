#include "mattermostuser.h"

MattermostUser::MattermostUser(QObject *parent) : QObject(parent)
{

}

QString MattermostUser::getUsername() const
{
    return username;
}

void MattermostUser::setUsername(const QString &value)
{
    username = value;
}

QString MattermostUser::getFirstname() const
{
    return firstname;
}

void MattermostUser::setFirstname(const QString &value)
{
    firstname = value;
}

QString MattermostUser::getLastname() const
{
    return lastname;
}

void MattermostUser::setLastname(const QString &value)
{
    lastname = value;
}

QString MattermostUser::getNickname() const
{
    return nickname;
}

void MattermostUser::setNickname(const QString &value)
{
    nickname = value;
}

QString MattermostUser::getId() const
{
    return id;
}

void MattermostUser::setId(const QString &value)
{
    id = value;
}
