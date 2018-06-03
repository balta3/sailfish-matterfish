#include "mattermostpost.h"

#include <QLocale>
#include <QJsonArray>
#include <QRegularExpression>

MattermostPost::MattermostPost(MattermostUser* user, QJsonObject &postJson, QObject *parent) : QObject(parent)
{
    this->user = user;
    this->message = postJson["message"].toString();
    qlonglong createdTimestamp = postJson["create_at"].toVariant().toLongLong();
    this->created.setTime_t(createdTimestamp / 1000);
    if (!postJson["file_ids"].isUndefined()) {
        QJsonArray fileArray = postJson["file_ids"].toArray();
        foreach (const QJsonValue &fileJson, fileArray) {
            QString fileId = fileJson.toString();
            MattermostFile* file = new MattermostFile(fileId, this);
            this->files << (file);
        }
    }
    this->processMarkdown();
}

QString MattermostPost::getMessage() const
{
    return this->message;
}

void MattermostPost::setMessage(const QString &value)
{
    this->message = value;
    this->processMarkdown();
    emit this->messageChanged(this->message);
}

QDateTime MattermostPost::getCreated() const
{
    return this->created;
}

QString MattermostPost::getCreatedDay() const
{
    return this->created.date().toString(QLocale::system().dateFormat(QLocale::LongFormat));
}

MattermostUser *MattermostPost::getUser() const
{
    return this->user;
}

QList<MattermostFile *> MattermostPost::getFiles() const
{
    return this->files;
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

void MattermostPost::processMarkdown() {
    this->message.replace(QRegularExpression("(https?:\\/\\/[^\\s]*)"), "<a href=\"\\1\">\\1</a>");
    this->message.replace(QRegularExpression("(?:[^\\w]|^)__(.+)__(?:[^\\w]|$)"), "<b>\\1</b>");
    this->message.replace(QRegularExpression("(?:[^\\w]|^)\\*\\*(.+)\\*\\*(?:[^\\w]|$)"), "<b>\\1</b>");
    this->message.replace(QRegularExpression("(?:[^\\w]|^)_(.+)_(?:[^\\w]|$)"), "<i>\\1</i>");
    this->message.replace(QRegularExpression("(?:[^\\w]|^)\\*(.+)\\*(?:[^\\w]|$)"), "<i>\\1</i>");
    this->message.replace(QRegularExpression("(?:[^\\w]|^)`(.+)`(?:[^\\w]|$)"), "<tt>\\1</tt>");
    this->message.replace(QRegularExpression("```(.+)```"), "<pre>\\1</pre>");
}
