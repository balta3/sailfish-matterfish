#ifndef MATTERMOSTTEAM_H
#define MATTERMOSTTEAM_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>

#include "mattermostchannel.h"
#include "mattermostteammember.h"

class MattermostTeam : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString displayName READ getDisplayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(QQmlListProperty<MattermostChannel> channels READ getChannelsQML NOTIFY channelsChanged)
    Q_PROPERTY(quint16 messageCount READ getMessageCount WRITE setMessageCount NOTIFY messageCountChanged)
    Q_PROPERTY(quint16 mentionCount READ getMentionCount WRITE setMentionCount NOTIFY mentionCountChanged)
public:
    explicit MattermostTeam(QObject *parent = nullptr);

    QString getId() const;
    void setId(const QString &value);

    QString getDisplayName() const;
    void setDisplayName(const QString &value);

    quint16 getMessageCount() const;
    void setMessageCount(quint16 value);

    quint16 getMentionCount() const;
    void setMentionCount(quint16 value);

    QList<MattermostChannel*> getChannels();
    void addChannel(MattermostChannel* channel);
    void clearChannels();
    QQmlListProperty<MattermostChannel> getChannelsQML();

    void clearMembers();
    void addMember(MattermostTeamMember* member);
    Q_INVOKABLE MattermostTeamMember* getMemberByDirectMessageChannelId(QString channelId);
    MattermostChannel* findChannelById(QString channelId);
    MattermostFile* findFileById(QString fileId);

signals:
    void idChanged(const QString &value);
    void displayNameChanged(const QString &value);
    void channelsChanged();
    void messageCountChanged(quint16 &value);
    void mentionCountChanged(quint16 &value);

public slots:

private:
    QString id;
    QString displayName;
    QList<MattermostChannel*> channels;
    QList<MattermostTeamMember*> members;
    quint16 messageCount;
    quint16 mentionCount;
    void sortChannels();
};

#endif // MATTERMOSTTEAM_H
