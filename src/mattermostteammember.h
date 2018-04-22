#ifndef MATTERMOSTTEAMMEMBER_H
#define MATTERMOSTTEAMMEMBER_H

#include <QObject>
#include <QDateTime>

class MattermostTeamMember : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userId READ getUserId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString channelId READ getChannelId WRITE setChannelId NOTIFY channelIdChanged)
    Q_PROPERTY(QDateTime lastViewed READ getLastViewed WRITE setLastViewed NOTIFY lastViewedChanged)
    Q_PROPERTY(QDateTime lastUpdated READ getLastUpdated WRITE setLastUpdated NOTIFY lastUpdatedChanged)
    Q_PROPERTY(bool unread READ isUnread NOTIFY unreadChanged)
    Q_PROPERTY(quint16 msgCount READ getMsgCount WRITE setMsgCount NOTIFY msgCountChanged)
public:
    explicit MattermostTeamMember(QObject *parent = nullptr);

    QString getUserId() const;
    void setUserId(const QString &value);

    QString getChannelId() const;
    void setChannelId(const QString &value);

    QDateTime getLastViewed() const;
    void setLastViewed(const QDateTime &value);

    QDateTime getLastUpdated() const;
    void setLastUpdated(const QDateTime &value);

    bool isUnread();

    quint16 getMsgCount() const;
    void setMsgCount(const quint16 &value);

signals:
    void userIdChanged(const QString& value);
    void channelIdChanged(const QString& value);
    void lastViewedChanged(const QDateTime& value);
    void lastUpdatedChanged(const QDateTime& value);
    void unreadChanged(const bool& value);
    void msgCountChanged(const quint16 &value);

public slots:

private:
    QString userId;
    QString channelId;
    QDateTime lastViewed;
    QDateTime lastUpdated;
    quint16 msgCount;
};

#endif // MATTERMOSTTEAMMEMBER_H
