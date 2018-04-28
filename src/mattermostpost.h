#ifndef MATTERMOSTPOST_H
#define MATTERMOSTPOST_H

#include <QObject>
#include <QDateTime>

#include "mattermostuser.h"

class MattermostPost : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ getMessage WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QDateTime created READ getCreated WRITE setCreated)
    Q_PROPERTY(MattermostUser* user READ getUser)
public:
    explicit MattermostPost(QObject *parent = nullptr);

    QString getMessage() const;
    void setMessage(const QString &value);

    QDateTime getCreated() const;
    void setCreated(const QDateTime &value);

    MattermostUser *getUser() const;
    void setUser(MattermostUser *value);

signals:
    void messageChanged(const QString* value);

public slots:

private:
    QString message;
    QDateTime created;
    MattermostUser* user;
};

#endif // MATTERMOSTPOST_H
