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
    this->webSocket = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this);
    QObject::connect(this->webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onWebSocketMessage(QString)));
    QObject::connect(this->webSocket, SIGNAL(connected()), this, SLOT(onWebSocketConnected()));
    QObject::connect(this->webSocket, SIGNAL(disconnected()), this, SLOT(onWebSocketDisconnected()));
    QObject::connect(this->webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onWebSocketError(QAbstractSocket::SocketError)));
    this->state = "offline";
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

    this->netAccessManager->post(request, payload);
}

void MattermostClient::disconnectFromHost()
{
    if (this->webSocket->isValid()) {
        this->webSocket->close();
    }
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

void MattermostClient::sendNewMessage(MattermostChannel* channel) {
    qDebug() << this->newMessage;
    QUrl postUrl = this->baseURL;
    postUrl.setPath("/api/v4/posts");

    QNetworkRequest request;
    request.setUrl(postUrl);
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bearer " + this->token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QVariantMap msgPost;
    msgPost["channel_id"] = channel->getId();
    msgPost["message"] = this->newMessage;
    QJsonDocument doc = QJsonDocument::fromVariant(msgPost);

    this->netAccessManager->post(request, doc.toJson());

    this->setNewMessage("");
}

void MattermostClient::initFile(QString fileId)
{
    if (this->loadingFileMetaIds.contains(fileId)) {
        return;
    }
    qDebug() << "init file" << fileId;
    this->loadingFileMetaIds << fileId;
    QUrl infoUrl = this->baseURL;
    infoUrl.setPath("/api/v4/files/" + fileId + "/info");

    QNetworkRequest request;
    request.setUrl(infoUrl);
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Bearer " + this->token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    this->netAccessManager->get(request);
}

MattermostFile *MattermostClient::getSelectedFile() const
{
    return selectedFile;
}

void MattermostClient::setSelectedFile(MattermostFile *value)
{
    this->selectedFile = value;
    emit this->selectedFileChanged(this->selectedFile);
}

QString MattermostClient::getState() const
{
    return this->state;
}

void MattermostClient::setState(const QString &value)
{
    this->state = value;
    emit this->stateChanged(this->state);
}

MattermostTeam* MattermostClient::findTeamById(QString teamId)
{
    return *std::find_if(this->teams.begin(), this->teams.end(), [teamId] (MattermostTeam* t) {return t->getId() == teamId; });
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
            QUrl websocketURL = this->baseURL;
            websocketURL.setScheme("wss");
            websocketURL.setPath("/api/v4/websocket");
            this->webSocket->open(websocketURL);
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
            this->messageCount = 0;
            this->mentionCount = 0;
            foreach (const QJsonValue &unreadJson, unreadsJson) {
                QJsonObject obj = unreadJson.toObject();
                QString teamId = obj["team_id"].toString();
                MattermostTeam* team = *std::find_if(this->teams.begin(), this->teams.end(), [teamId] (MattermostTeam* t) {return t->getId() == teamId; });
                if (team) {
                    team->setMessageCount(obj["msg_count"].toInt());
                    team->setMentionCount(obj["mention_count"].toInt());
                    this->messageCount += obj["msg_count"].toInt();
                    this->mentionCount += obj["mention_count"].toInt();
                } else {
                    qDebug() << "cannot find team" << teamId;
                }
            }
            emit this->messageCountChanged(this->messageCount);
            emit this->mentionCountChanged(this->mentionCount);
        } else if (path.endsWith("channels")) {
            qDebug() << "channels";
            QStringList pathParts = path.split("/");
            QString teamId = pathParts[pathParts.size() - 2];
            MattermostTeam* team = this->findTeamById(teamId);
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
            MattermostTeam* team = this->findTeamById(teamId);
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
                MattermostChannel* channel = team->findChannelById(member->getChannelId());
                if (channel) {
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
        } else if (path.endsWith("/posts") && path.contains("/channels/")) {
            qDebug() << "posts";
            QStringList pathParts = path.split("/");
            QString channelId = pathParts[pathParts.size() - 2];
            MattermostChannel* channel = this->selectedTeam->findChannelById(channelId);
            if (channel) {
                QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
                channel->updatePosts(doc, this->users);
            }
        } else if (path.endsWith("/info") && path.contains("/files/")) {
            qDebug() << "fileInfo";
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject fileJson = doc.object();
            QString fileId = fileJson["id"].toString();
            foreach(MattermostTeam* team, this->teams) {
                MattermostFile *file = team->findFileById(fileId);
                if (file) {
                    file->setName(fileJson["name"].toString());
                    file->setExtension(fileJson["extension"].toString());
                    file->setMimeType(fileJson["mime_type"].toString());
                    file->setSize(fileJson["size"].toInt());
                    file->setHasPreviewImage(fileJson["has_preview_image"].toBool());
                }
            }
            this->loadingFileMetaIds.removeOne(fileId);
        } else {
            qDebug() << "unknown reply: " << path;
        }
    } else {
        qDebug() << "response error: " << reply->errorString();
    }
}

void MattermostClient::onWebSocketConnected() {
    this->webSocketSeq = 1;
    QVariantMap websocketAuthMap;
    QVariantMap websocketAuthMapData;
    websocketAuthMapData["token"] = this->token;
    websocketAuthMap["seq"] = this->webSocketSeq++;
    websocketAuthMap["action"] = "authentication_challenge";
    websocketAuthMap["data"] = websocketAuthMapData;
    QJsonDocument websocketAuthJson = QJsonDocument::fromVariant(websocketAuthMap);
    this->webSocket->sendTextMessage(QString(websocketAuthJson.toJson()));
    this->setState("online");
}

void MattermostClient::onWebSocketDisconnected() {
    this->setState("offline");
}

void MattermostClient::onWebSocketMessage(QString messageStr) {
    QJsonDocument messageDoc = QJsonDocument::fromJson(messageStr.toUtf8());
    QJsonObject message = messageDoc.object();
    if (message.contains("status") && message.contains("seq_reply")) {
        qDebug() << "Seq" << message["seq_reply"].toInt() << "status" << message["status"].toString();
    } else if (message.contains("event") && message.contains("data")) {
        QString event = message["event"].toString();
        QJsonObject data = message["data"].toObject();
        QJsonObject broadcast = message["broadcast"].toObject();
        if (event == "hello") {
            qDebug() << "Server version" << data["server_version"].toString();
        } else if (event == "posted") {
            qDebug() << "New post in channel" << data["channel_name"].toString();
            QString channelId = broadcast["channel_id"].toString();
            foreach (MattermostTeam* team, this->teams) {
                MattermostChannel* channel = team->findChannelById(channelId);
                if (channel) {
                    QString postJson = data["post"].toString();
                    QJsonDocument postDoc = QJsonDocument::fromJson(postJson.toUtf8());
                    QJsonObject postJsonObj = postDoc.object();
                    channel->addPost(postJsonObj, this->users);
                }
            }
            this->refreshTeamUnreads();
        } else if (event == "channel_viewed") {
            QString channelId = data["channel_id"].toString();
            qDebug() << "Channel viewed:" << channelId;
            foreach (MattermostTeam* team, this->teams) {
                MattermostChannel* channel = team->findChannelById(channelId);
                if (channel) {
                    channel->getMember()->setLastViewed(QDateTime::currentDateTime());
                }
            }
            this->refreshTeamUnreads();
        } else {
            qDebug() << "Unknown event:" << event << messageStr;
        }
    } else {
        qDebug() << "Got unknown message" << messageStr;
    }
}

void MattermostClient::onWebSocketError(QAbstractSocket::SocketError error) {
    Q_UNUSED(error)
    qDebug() << "websocket error" << this->webSocket->errorString();
    this->setState("offline");
}

QString MattermostClient::getNewMessage() const
{
    return newMessage;
}

void MattermostClient::setNewMessage(const QString &value)
{
    newMessage = value;
    emit this->newMessageChanged(this->newMessage);
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

quint16 MattermostClient::getMessageCount() const {
    return this->messageCount;
}

quint16 MattermostClient::getMentionCount() const {
    return this->mentionCount;
}

void MattermostClient::setMessageCount(quint16 value) {
    this->messageCount = value;
    emit this->messageCountChanged(this->messageCount);
}

void MattermostClient::setMentionCount(quint16 value) {
    this->mentionCount = value;
    emit this->mentionCountChanged(this->mentionCount);
}
