#ifndef MATTERMOSTTEAMMEMBER_H
#define MATTERMOSTTEAMMEMBER_H

#include <QObject>

class MattermostTeamMember : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userId READ getUserId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString channelId READ getChannelId WRITE setChannelId NOTIFY channelIdChanged)
public:
    explicit MattermostTeamMember(QObject *parent = nullptr);

    QString getUserId() const;
    void setUserId(const QString &value);

    QString getChannelId() const;
    void setChannelId(const QString &value);

signals:
    void userIdChanged(const QString& value);
    void channelIdChanged(const QString& value);

public slots:

private:
    QString userId;
    QString channelId;
};

#endif // MATTERMOSTTEAMMEMBER_H
