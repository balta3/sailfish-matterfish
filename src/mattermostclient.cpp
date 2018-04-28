#include "mattermostclient.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

MattermostClient::MattermostClient(QObject *parent) : QObject(parent)
{
    this->netAccessManager = new QNetworkAccessManager(this);
    QObject::connect(this->netAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResponse(QNetworkReply*)));
}

QString MattermostClient::getHost() const
{
    return host;
}

void MattermostClient::setHost(const QString &value)
{
    host = value;
}

QString MattermostClient::getUsername() const
{
    return username;
}

void MattermostClient::setUsername(const QString &value)
{
    username = value;
}

QString MattermostClient::getPassword() const
{
    return password;
}

void MattermostClient::setPassword(const QString &value)
{
    password = value;
}

void MattermostClient::connectToHost() {
    this->baseURL.setScheme("https");
    this->baseURL.setHost(this->host);
    emit this->baseURLChanged(this->baseURL);

    QUrl loginURL = this->baseURL;
    loginURL.setPath("/api/v4/users/login");

    QNetworkRequest request;
    request.setUrl(loginURL);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QVariantMap loginData;
    loginData.insert("login_id", this->username);
    loginData.insert("password", this->password);
    QByteArray payload = QJsonDocument::fromVariant(loginData).toJson();

    qDebug() << payload;

    this->netAccessManager->post(request, payload);
}

void MattermostClient::refreshTeams() {
    QUrl teamsURL = this->baseURL;
    teamsURL.setPath("/api/v4/users/" + this->user["id"].toString() + "/teams");

    QNetworkRequest request;
    request.setUrl(teamsURL);
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bearer " + this->token).toUtf8());

    this->netAccessManager->get(request);
}

void MattermostClient::refreshTeamUnreads() {
    QUrl teamsURL = this->baseURL;
    teamsURL.setPath("/api/v4/users/" + this->user["id"].toString() + "/teams/unread");

    QNetworkRequest request;
    request.setUrl(teamsURL);
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bearer " + this->token).toUtf8());

    this->netAccessManager->get(request);
}

void MattermostClient::refreshChannels(MattermostTeam* team) {
    QUrl channelsUrl = this->baseURL;
    channelsUrl.setPath("/api/v4/users/" + this->user["id"].toString() + "/teams/" + team->getId() + "/channels");

    QNetworkRequest request;
    request.setUrl(channelsUrl);
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bearer " + this->token).toUtf8());

    this->netAccessManager->get(request);
}

void MattermostClient::refreshTeamMembers(MattermostTeam *team) {
    QUrl channelsUrl = this->baseURL;
    channelsUrl.setPath("/api/v4/users/" + this->user["id"].toString() + "/teams/" + team->getId() + "/channels/members");

    QNetworkRequest request;
    request.setUrl(channelsUrl);
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bearer " + this->token).toUtf8());

    this->netAccessManager->get(request);
}

void MattermostClient::refreshUsers() {
    QUrl usersURL = this->baseURL;
    usersURL.setPath("/api/v4/users");
    usersURL.setQuery(QUrlQuery("per_page=200"));

    QNetworkRequest request;
    request.setUrl(usersURL);
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bearer " + this->token).toUtf8());

    this->netAccessManager->get(request);
}

void MattermostClient::refreshChannelPosts(MattermostChannel *channel) {
    QUrl channelsUrl = this->baseURL;
    channelsUrl.setPath("/api/v4/channels/" + channel->getId() + "/posts");

    QNetworkRequest request;
    request.setUrl(channelsUrl);
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bearer " + this->token).toUtf8());

    this->netAccessManager->get(request);
}

void MattermostClient::onResponse(QNetworkReply *reply) {
    QNetworkReply::NetworkError error = reply->error();
    if (error == QNetworkReply::NoError) {
        QString path = reply->request().url().path();
        qDebug() << path;
        if (path.endsWith("login")) {
            this->token = QString(reply->rawHeader("Token"));
            qDebug() << "Token:" << this->token;
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            this->user = doc.object().toVariantMap();
            this->refreshUsers();
        } else if (path.endsWith("teams")) {
            qDebug() << "teams";
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            this->teams.clear();
            QJsonArray teamsJson = doc.array();
            foreach (const QJsonValue &teamJson, teamsJson) {
                QJsonObject obj = teamJson.toObject();
                MattermostTeam* team = new MattermostTeam(this);
                team->setId(obj["id"].toString());
                team->setDisplayName(obj["display_name"].toString());
                this->teams.append(team);
            }
            emit this->teamsChanged();
            foreach (MattermostTeam* team, this->teams) {
                qDebug() << "refresh team:" << team->getDisplayName();
                this->refreshTeamUnreads();
                this->refreshChannels(team);
            }
        } else if (path.endsWith("teams/unread")) {
            qDebug() << "team unreads";
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonArray unreadsJson = doc.array();
            foreach (const QJsonValue &unreadJson, unreadsJson) {
                QJsonObject obj = unreadJson.toObject();
                QString teamId = obj["team_id"].toString();
                MattermostTeam* team = *std::find_if(this->teams.begin(), this->teams.end(), [teamId] (MattermostTeam* t) {return t->getId() == teamId; });
                if (team) {
                    team->setMessageCount(obj["msg_count"].toInt());
                    team->setMentionCount(obj["mention_count"].toInt());
                } else {
                    qDebug() << "cannot find team" << teamId;
                }
            }
        } else if (path.endsWith("channels")) {
            qDebug() << "channels";
            QStringList pathParts = path.split("/");
            QString teamId = pathParts[pathParts.size() - 2];
            MattermostTeam* team = *std::find_if(this->teams.begin(), this->teams.end(), [teamId] (MattermostTeam* t) {return t->getId() == teamId; });
            team->clearChannels();
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonArray channelsJson = doc.array();
            foreach (const QJsonValue &channelJson, channelsJson) {
                QJsonObject obj = channelJson.toObject();
                MattermostChannel* channel = new MattermostChannel(team);
                channel->setId(obj["id"].toString());
                channel->setName(obj["name"].toString());
                channel->setDisplayName(obj["display_name"].toString());
                channel->setType(obj["type"].toString());
                channel->setTotalMsgCount(obj["total_msg_count"].toInt());
                qlonglong lastUpdateTimestamp = obj["update_at"].toVariant().toLongLong();
                QDateTime lastUpdate;
                lastUpdate.setTime_t(lastUpdateTimestamp / 1000);
                channel->setLastUpdated(lastUpdate);
                qlonglong lastPostAtTimestamp = obj["last_post_at"].toVariant().toLongLong();
                QDateTime lastPostAt;
                lastPostAt.setTime_t(lastPostAtTimestamp / 1000);
                channel->setLastPostAt(lastPostAt);
                team->addChannel(channel);
                if (channel->getType() == "D") {
                    QString userId = channel->getName().remove(this->user["id"].toString()).remove("_");
                    if (this->users.contains(userId)) {
                        channel->setDisplayName(this->users[userId]->getUsername());
                    } else {
                        qDebug() << "missing user id" << userId;
                    }
                }
            }
            this->refreshTeamMembers(team);
        } else if (path.endsWith("channels/members")) {
            qDebug() << "members";
            QStringList pathParts = path.split("/");
            QString teamId = pathParts[pathParts.size() - 3];
            MattermostTeam* team = *std::find_if(this->teams.begin(), this->teams.end(), [teamId] (MattermostTeam* t) {return t->getId() == teamId; });
            team->clearMembers();
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonArray membersJson = doc.array();
            foreach (const QJsonValue &memberJson, membersJson) {
                QJsonObject obj = memberJson.toObject();
                MattermostTeamMember* member = new MattermostTeamMember(team);
                member->setUserId(obj["user_id"].toString());
                member->setChannelId(obj["channel_id"].toString());
                qlonglong lastUpdateTimestamp = obj["last_update_at"].toVariant().toLongLong();
                qlonglong lastViewedTimestamp = obj["last_viewed_at"].toVariant().toLongLong();
                QDateTime lastUpdate;
                lastUpdate.setTime_t(lastUpdateTimestamp / 1000);
                QDateTime lastViewed;
                lastViewed.setTime_t(lastViewedTimestamp / 1000);
                member->setLastUpdated(lastUpdate);
                member->setLastViewed(lastViewed);
                member->setMsgCount(obj["msg_count"].toInt());
                team->addMember(member);
                QList<MattermostChannel*> channels = team->getChannels();
                QList<MattermostChannel*>::iterator channelIt = std::find_if(channels.begin(), channels.end(), [member] (MattermostChannel* c) {return c->getId() == member->getChannelId(); });
                if (*channelIt && channelIt != team->getChannels().end()) {
                    MattermostChannel* channel = *channelIt;
                    channel->setMember(member);
                }
            }
        } else if (path.endsWith("/users")) {
            qDebug() << "users";
            this->users.clear();
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonArray usersJson = doc.array();
            foreach (const QJsonValue &userJson, usersJson) {
                QJsonObject obj = userJson.toObject();
                MattermostUser* user = new MattermostUser(this);
                user->setId(obj["id"].toString());
                user->setUsername(obj["username"].toString());
                user->setFirstname(obj["first_name"].toString());
                user->setLastname(obj["last_name"].toString());
                user->setNickname(obj["nickname"].toString());
                this->users.insert(user->getId(), user);
            }
            qDebug() << "got" << this->users.size() << "users";
            this->refreshTeams();
        } else if (path.endsWith("/posts")) {
            qDebug() << "posts";
            QStringList pathParts = path.split("/");
            QString channelId = pathParts[pathParts.size() - 2];
            MattermostChannel* channel;
            foreach (MattermostTeam* team, this->teams) {
                QList<MattermostChannel*> channels = team->getChannels();
                QList<MattermostChannel*>::iterator channelIt = std::find_if(channels.begin(), channels.end(), [channelId] (MattermostChannel* c) {return c->getId() == channelId;});
                if (*channelIt && channelIt != channels.end()) {
                    channel = *channelIt;
                }
            }
            if (channel) {
                channel->clearPosts();
                QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
                QJsonObject container = doc.object();
                QJsonArray orderArray = container["order"].toArray();
                QJsonObject posts = container["posts"].toObject();
                foreach (const QJsonValue &orderJson, orderArray) {
                    QString postId = orderJson.toString();
                    QJsonObject postJson = posts[postId].toObject();
                    MattermostPost* post = new MattermostPost(channel);
                    post->setMessage(postJson["message"].toString());
                    qlonglong createdTimestamp = postJson["create_at"].toVariant().toLongLong();
                    QDateTime created;
                    created.setTime_t(createdTimestamp / 1000);
                    post->setCreated(created);
                    MattermostUser* user = this->users[postJson["user_id"].toString()];
                    post->setUser(user);
                    channel->addPost(post);
                }
            }
        } else {
            qDebug() << "unknown reply: " << path;
        }
    } else {
        qDebug() << "response error: " << reply->errorString();
    }
}

QUrl MattermostClient::getBaseURL() const
{
    return baseURL;
}

void MattermostClient::setBaseURL(const QUrl &value)
{
    baseURL = value;
}

QString MattermostClient::getAuthorization()
{
    return QString("Bearer " + this->token);
}

MattermostChannel *MattermostClient::getSelectedChannel() const
{
    return selectedChannel;
}

void MattermostClient::setSelectedChannel(MattermostChannel *value)
{
    selectedChannel = value;
    emit this->selectedChannelChanged(this->selectedChannel);
    this->refreshChannelPosts(value);
}

MattermostTeam *MattermostClient::getSelectedTeam() const
{
    return selectedTeam;
}

void MattermostClient::setSelectedTeam(MattermostTeam *value)
{
    selectedTeam = value;
    emit this->selectedTeamChanged(value);
}

QQmlListProperty<MattermostTeam> MattermostClient::getTeamsQML() {
    return QQmlListProperty<MattermostTeam>(this, this->teams);
}
