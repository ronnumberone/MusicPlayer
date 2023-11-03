#ifndef AUDIOSEARCHMODEL_H
#define AUDIOSEARCHMODEL_H

#include <QAbstractListModel>
#include <QNetworkAccessManager>

class AudioInfo;

class AudioSearchModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool isSearching READ isSearching NOTIFY isSearchingChanged FINAL)

public:
    enum Role{
        AudioTitleRole=Qt::UserRole+1,
        AudioAuthorRole,
        AudioImageRole,
        AudioSourceRole
    };
    explicit AudioSearchModel(QObject *parent = nullptr);
    bool isSearching() const;
    void setIsSearching(bool newIsSearching);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void searchSong(const QString &name);
    void parseData();

signals:
    void isSearchingChanged();

private:
    bool m_isSearching = false;
    QList<AudioInfo*> m_audioList;
    QNetworkAccessManager m_networkManager;
    QNetworkReply *m_reply = nullptr;
};

#endif // AUDIOSEARCHMODEL_H
