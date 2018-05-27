#include "mattermostfile.h"

MattermostFile::MattermostFile(QString id, QObject *parent) : QObject(parent)
{
    this->id = id;
}

QString MattermostFile::getId() const
{
    return this->id;
}

QString MattermostFile::getName() const
{
    return this->name;
}

void MattermostFile::setName(const QString &value)
{
    this->name = value;
    emit this->nameChanged(this->name);
}

QString MattermostFile::getExtension() const
{
    return this->extension;
}

void MattermostFile::setExtension(const QString &value)
{
    this->extension = value;
}

QString MattermostFile::getMimeType() const
{
    return this->mimeType;
}

void MattermostFile::setMimeType(const QString &value)
{
    this->mimeType = value;
    emit this->mimeTypeChanged(this->mimeType);
}

quint64 MattermostFile::getSize() const
{
    return this->size;
}

void MattermostFile::setSize(const quint64 &value)
{
    this->size = value;
}

bool MattermostFile::getHasPreviewImage() const
{
    return this->hasPreviewImage;
}

void MattermostFile::setHasPreviewImage(bool value)
{
    this->hasPreviewImage = value;
    emit this->hasPreviewImageChanged(this->hasPreviewImage);
}
