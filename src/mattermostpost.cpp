#include "mattermostpost.h"

#include <QLocale>

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

QString MattermostPost::getCreatedDay() const
{
    return created.date().toString(QLocale::system().dateFormat(QLocale::LongFormat));
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

QList<MattermostFile *> MattermostPost::getFiles() const
{
    return files;
}

QQmlListProperty<MattermostFile> MattermostPost::getFilesQML()
{
    return QQmlListProperty<MattermostFile>(this, this->files);
}

void MattermostPost::addFile(MattermostFile *file)
{
    this->files << file;
    emit this->filesChanged();
}
