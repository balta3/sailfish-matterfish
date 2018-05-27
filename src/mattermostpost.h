#ifndef MATTERMOSTPOST_H
#define MATTERMOSTPOST_H

#include <QObject>
#include <QDateTime>
#include <QQmlListProperty>
#include <QJsonObject>

#include "mattermostuser.h"
#include "mattermostfile.h"

class MattermostPost : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ getMessage WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QDateTime created READ getCreated CONSTANT)
    Q_PROPERTY(QString createdDay READ getCreatedDay CONSTANT)
    Q_PROPERTY(MattermostUser* user READ getUser CONSTANT)
    Q_PROPERTY(QQmlListProperty<MattermostFile> files READ getFilesQML NOTIFY filesChanged)
public:
    explicit MattermostPost(MattermostUser* user, QJsonObject &postJson, QObject *parent = nullptr);

    QString getMessage() const;
    void setMessage(const QString &value);

    QDateTime getCreated() const;

    QString getCreatedDay() const;

    MattermostUser *getUser() const;

    QList<MattermostFile *> getFiles() const;
    QQmlListProperty<MattermostFile> getFilesQML();
    void addFile(MattermostFile* file);

signals:
    void messageChanged(const QString& value);
    void filesChanged();

public slots:

private:
    QString message;
    QDateTime created;
    MattermostUser* user;
    QList<MattermostFile*> files;
};

#endif // MATTERMOSTPOST_H
