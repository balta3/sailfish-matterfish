#ifndef MATTERMOSTCLIENT_H
#define MATTERMOSTCLIENT_H

#include <QObject>
#include <QVariantMap>
#include <QList>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QQmlListProperty>

#include "mattermostteam.h"

class MattermostClient : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(MattermostTeam* selectedTeam READ getSelectedTeam WRITE setSelectedTeam NOTIFY selectedTeamChanged)
    Q_PROPERTY(QQmlListProperty<MattermostTeam> teams READ getTeamsQML NOTIFY teamsChanged)
public:
    explicit MattermostClient(QObject *parent = nullptr);

    QString getHost() const;
    void setHost(const QString &value);

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    MattermostTeam *getSelectedTeam() const;
    void setSelectedTeam(MattermostTeam *value);

    QQmlListProperty<MattermostTeam> getTeamsQML();

signals:
    void hostChanged(const QString& host);
    void usernameChanged(const QString& username);
    void passwordChanged(const QString& password);
    void selectedTeamChanged(const MattermostTeam* team);
    void teamsChanged();
public slots:
    void connectToHost();
    void refreshTeams();
    void refreshChannels(MattermostTeam* team);
    void refreshTeamMembers(MattermostTeam* team);
    void onResponse(QNetworkReply* reply);

private:
    QString host;
    QString username;
    QString password;
    QVariantMap user;
    QList<MattermostTeam*> teams;

    MattermostTeam* selectedTeam;

    QUrl baseURL;
    QNetworkAccessManager* netAccessManager;
    QString token;
};

#endif // MATTERMOSTCLIENT_H
