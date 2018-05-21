#ifndef MATTERMOSTFILE_H
#define MATTERMOSTFILE_H

#include <QObject>

class MattermostFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString mimeType READ getMimeType WRITE setMimeType NOTIFY mimeTypeChanged)
    Q_PROPERTY(bool hasPreviewImage READ getHasPreviewImage WRITE setHasPreviewImage NOTIFY hasPreviewImageChanged)
public:
    explicit MattermostFile(QObject *parent = nullptr);

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getExtension() const;
    void setExtension(const QString &value);

    QString getMimeType() const;
    void setMimeType(const QString &value);

    quint64 getSize() const;
    void setSize(const quint64 &value);

    bool getHasPreviewImage() const;
    void setHasPreviewImage(bool value);

signals:
    void nameChanged(const QString& value);
    void mimeTypeChanged(const QString& value);
    void hasPreviewImageChanged(const bool& value);

public slots:

private:
    QString id;
    QString name;
    QString extension;
    QString mimeType;
    quint64 size;
    bool hasPreviewImage;
};

#endif // MATTERMOSTFILE_H
