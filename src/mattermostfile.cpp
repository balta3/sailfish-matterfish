#include "mattermostfile.h"

MattermostFile::MattermostFile(QObject *parent) : QObject(parent)
{

}

QString MattermostFile::getId() const
{
    return id;
}

void MattermostFile::setId(const QString &value)
{
    id = value;
}

QString MattermostFile::getName() const
{
    return name;
}

void MattermostFile::setName(const QString &value)
{
    this->name = value;
    emit this->nameChanged(this->name);
}

QString MattermostFile::getExtension() const
{
    return extension;
}

void MattermostFile::setExtension(const QString &value)
{
    extension = value;
}

QString MattermostFile::getMimeType() const
{
    return mimeType;
}

void MattermostFile::setMimeType(const QString &value)
{
    this->mimeType = value;
    emit this->mimeTypeChanged(this->mimeType);
}

quint64 MattermostFile::getSize() const
{
    return size;
}

void MattermostFile::setSize(const quint64 &value)
{
    size = value;
}

bool MattermostFile::getHasPreviewImage() const
{
    return hasPreviewImage;
}

void MattermostFile::setHasPreviewImage(bool value)
{
    this->hasPreviewImage = value;
    emit this->hasPreviewImageChanged(this->hasPreviewImage);
}
