#ifndef MATTERMOSTCHANNEL_H
#define MATTERMOSTCHANNEL_H

#include <QObject>

class MattermostChannel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString displayName READ getDisplayName WRITE setDisplayName NOTIFY displayNameChanged)
public:
    explicit MattermostChannel(QObject *parent = nullptr);

    QString getId() const;
    void setId(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QString getDisplayName() const;
    void setDisplayName(const QString &value);

signals:
    void idChanged(const QString &value);
    void typeChanged(const QString &value);
    void displayNameChanged(const QString &value);

public slots:

private:
    QString id;
    QString type;
    QString displayName;
};

#endif // MATTERMOSTCHANNEL_H
