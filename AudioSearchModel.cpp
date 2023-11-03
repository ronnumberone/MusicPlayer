#include "AudioSearchModel.h"
#include "AudioInfo.h"
#include <QJsonDocument>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

namespace {
const QString &k_requestUrl = "https://api.jamendo.com/v3.0/tracks/";
const QString &k_clientId = "eb95d913";
}

AudioSearchModel::AudioSearchModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

bool AudioSearchModel::isSearching() const
{
    return m_isSearching;
}

void AudioSearchModel::setIsSearching(bool newIsSearching)
{
    if (m_isSearching == newIsSearching)
        return;
    m_isSearching = newIsSearching;
    emit isSearchingChanged();
}

int AudioSearchModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_audioList.length();
}

QVariant AudioSearchModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row()>=0 && index.row()<m_audioList.length()){
        AudioInfo *audioInfo = m_audioList[index.row()];

        switch((Role) role){
        case AudioTitleRole :
            return audioInfo->audioTitle();
        case AudioAuthorRole:
            return audioInfo->audioAuthor();
        case AudioImageRole:
            return audioInfo->audioImage();
        case AudioSourceRole:
            return audioInfo->audioSource();
        }
    }
    return {};
}

QHash<int, QByteArray> AudioSearchModel::roleNames() const
{
    QHash<int, QByteArray> result;

    result[AudioTitleRole] = "audioTitle";
    result[AudioAuthorRole] = "audioAuthor";
    result[AudioImageRole] = "audioImage";
    result[AudioSourceRole] = "audioSource";

    return result;
}

void AudioSearchModel::searchSong(const QString &name)
{
    if(!name.trimmed().isEmpty()){
        if(m_reply){
            m_reply->abort();
            m_reply->deleteLater();
            m_reply = nullptr;
        }

        QUrlQuery query;
        query.addQueryItem("client_id", k_clientId);
        query.addQueryItem("namesearch", name);
        query.addQueryItem("format", "json");

        m_isSearching = true;
        emit isSearchingChanged();

        m_reply = m_networkManager.get(QNetworkRequest(k_requestUrl + "?" + query.toString()));
        connect(m_reply, &QNetworkReply::finished, this, &AudioSearchModel::parseData);
    }
}

void AudioSearchModel::parseData()
{
    if(m_reply->error() == QNetworkReply::NoError){
        beginResetModel();

        qDeleteAll(m_audioList);
        m_audioList.clear();

        QByteArray data = m_reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject headers = jsonDocument["headers"].toObject();
        if(headers["status"].toString() == "success"){
            QJsonArray results = jsonDocument["results"].toArray();
            for(const auto &result : results){
                QJsonObject entry = result.toObject();
                if(entry["audiodownload_allowed"].toBool()){
                    AudioInfo *audioInfo = new AudioInfo(this);
                    audioInfo->setAudioTitle(entry["name"].toString());
                    audioInfo->setAudioAuthor(entry["artist_name"].toString());
                    audioInfo->setAudioSource(entry["audio"].toString());
                    audioInfo->setAudioImage(entry["image"].toString());

                    m_audioList << audioInfo;
                }
            }
        }else{
            qWarning() << headers["error_string"];
        }

        endResetModel();
    }else if(m_reply->error() != QNetworkReply::OperationCanceledError){
        qCritical() << "Reply failed, error: " << m_reply->errorString();
    }
    m_isSearching = false;
    emit isSearchingChanged();
    m_reply->deleteLater();
    m_reply = nullptr;
}
