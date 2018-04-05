#include "mattermostchannel.h"

MattermostChannel::MattermostChannel(QObject *parent) : QObject(parent)
{

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
