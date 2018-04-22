#ifndef MATTERMOSTCHANNEL_H
#define MATTERMOSTCHANNEL_H

#include <QObject>

#include "mattermostteammember.h"

class MattermostChannel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString displayName READ getDisplayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(MattermostTeamMember* member READ getMember WRITE setMember NOTIFY memberChanged)
    Q_PROPERTY(bool unread READ isUnread NOTIFY unreadChanged)
    Q_PROPERTY(uint totalMsgCount READ getTotalMsgCount WRITE setTotalMsgCount NOTIFY totalMsgCountChanged)
    Q_PROPERTY(QDateTime lastUpdated READ getLastUpdated WRITE setLastUpdated NOTIFY lastUpdatedChanged)
    Q_PROPERTY(QDateTime lastPostAt READ getLastPostAt WRITE setLastPostAt NOTIFY lastPostAtChanged)
public:
    explicit MattermostChannel(QObject *parent = nullptr);

    QString getId() const;
    void setId(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getDisplayName() const;
    void setDisplayName(const QString &value);

    QDateTime getLastUpdated() const;
    void setLastUpdated(const QDateTime &value);

    MattermostTeamMember *getMember() const;
    void setMember(MattermostTeamMember *value);

    bool isUnread();

    uint getTotalMsgCount() const;
    void setTotalMsgCount(const uint &value);

    QDateTime getLastPostAt() const;
    void setLastPostAt(const QDateTime &value);

signals:
    void idChanged(const QString &value);
    void typeChanged(const QString &value);
    void nameChanged(const QString &value);
    void displayNameChanged(const QString &value);
    void memberChanged(const MattermostTeamMember &value);
    void unreadChanged(const bool &value);
    void totalMsgCountChanged(const uint &value);
    void lastUpdatedChanged(const QDateTime &value);
    void lastPostAtChanged(const QDateTime &value);

public slots:

private:
    QString id;
    QString type;
    QString name;
    QString displayName;
    QDateTime lastUpdated;
    QDateTime lastPostAt;
    MattermostTeamMember* member;
    uint totalMsgCount;
};

#endif // MATTERMOSTCHANNEL_H
