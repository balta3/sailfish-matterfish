#ifndef MATTERMOSTUSER_H
#define MATTERMOSTUSER_H

#include <QObject>

class MattermostUser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString firstname READ getFirstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QString lastname READ getLastname WRITE setLastname NOTIFY lastnameChanged)
    Q_PROPERTY(QString nickname READ getNickname WRITE setNickname NOTIFY nicknameChanged)
public:
    explicit MattermostUser(QObject *parent = nullptr);

    QString getId() const;
    void setId(const QString &value);

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getFirstname() const;
    void setFirstname(const QString &value);

    QString getLastname() const;
    void setLastname(const QString &value);

    QString getNickname() const;
    void setNickname(const QString &value);

signals:
    void idChanged(const QString &value);
    void usernameChanged(const QString &value);
    void firstnameChanged(const QString &value);
    void lastnameChanged(const QString &value);
    void nicknameChanged(const QString &value);

public slots:

private:
    QString id;
    QString username;
    QString firstname;
    QString lastname;
    QString nickname;
};

#endif // MATTERMOSTUSER_H
