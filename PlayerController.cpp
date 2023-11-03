#include "PlayerController.h"
#include "AudioInfo.h"
#include <QMediaDevices>
#include <QAudioDevice>
#include <QAudioOutput>
#include <QDebug>

PlayerController::PlayerController(QObject *parent)
    :QAbstractListModel(parent)
{
    const auto &audioOutputs = QMediaDevices::audioOutputs();
    if (!audioOutputs.isEmpty()) {
        m_audioOutput = new QAudioOutput(&m_mediaPlayer);
        m_mediaPlayer.setAudioOutput(m_audioOutput);
    }

    addAudio("Snowman",
             "Sia",
             QUrl("assets/images/song1.png"),
             QUrl("qrc:/MusicPlayer/assets/audios/song1.mp3"));

    addAudio("We don't talk anymore",
             "Charlie Puth ft Selena Gomez",
             QUrl("assets/images/song2.jpg"),
             QUrl("qrc:/MusicPlayer/assets/audios/song2.mp3"));

    addAudio("Lovely",
             "Billie Eilish",
             QUrl("assets/images/song3.jpg"),
             QUrl("qrc:/MusicPlayer/assets/audios/song3.mp3"));

    //    addAudio("Senorita",
    //             "Camila Cabello",
    //             QUrl("assets/images/song4.jpg"),
    //             QUrl("qrc:/MusicPlayer/assets/audios/song4.mp3"));
}

AudioInfo *PlayerController::currentSong() const
{
    return m_currentSong;
}

void PlayerController::setCurrentSong(AudioInfo *newCurrentSong)
{
    if (m_currentSong == newCurrentSong)
        return;
    m_currentSong = newCurrentSong;
    emit currentSongChanged();

    if(m_currentSong){
        changeAudioSource(m_currentSong->audioSource());
    }else{
        m_mediaPlayer.stop();
        m_mediaPlayer.setSource(QUrl());
        m_isPlaying=false;
        emit isPlayingChanged();
    }
}

bool PlayerController::isPlaying() const
{
    return m_isPlaying;
}

void PlayerController::switchToNextSong()
{
    if(m_isRandom){
        if (m_randomSongList.isEmpty()) {
            // Nếu danh sách bài hát đã xáo trộn đã rỗng, tạo một danh sách mới và xáo trộn nó
            m_randomSongList = m_audioList;
            m_randomSongList.removeAt(m_audioList.indexOf(m_currentSong));
            std::random_shuffle(m_randomSongList.begin(), m_randomSongList.end());
        }

        // Chọn bài hát theo thứ tự từ danh sách xáo trộn
        setCurrentSong(m_randomSongList.first());

        // Loại bỏ bài hát đã chọn từ danh sách xáo trộn
        m_randomSongList.pop_front();
    }else{
        int index = m_audioList.indexOf(m_currentSong);
        if (index + 1 >= m_audioList.length()) {
            setCurrentSong(m_audioList.first());
        } else {
            setCurrentSong(m_audioList[index + 1]);
        }
    }
}

void PlayerController::switchToPreviousSong()
{
    if(m_isRandom){
        if (m_randomSongList.isEmpty()) {
            // Nếu danh sách bài hát đã xáo trộn đã rỗng, tạo một danh sách mới và xáo trộn nó
            m_randomSongList = m_audioList;
            m_randomSongList.removeAt(m_audioList.indexOf(m_currentSong));
            std::random_shuffle(m_randomSongList.begin(), m_randomSongList.end());
        }

        // Chọn bài hát theo thứ tự từ danh sách xáo trộn
        setCurrentSong(m_randomSongList.first());

        // Loại bỏ bài hát đã chọn từ danh sách xáo trộn
        m_randomSongList.pop_front();
    }else{
        int index = m_audioList.indexOf(m_currentSong);
        if(index <= 0){
            setCurrentSong(m_audioList.last());
        }else{
            setCurrentSong(m_audioList[index-1]);
        }
    }
}

void PlayerController::switchToSongByIndex(int index)
{
    if(index>=0 && index<m_audioList.length()){
        setCurrentSong(m_audioList[index]);
    }
}

void PlayerController::changeAudioSource(const QUrl &source){
    m_mediaPlayer.stop();
    m_mediaPlayer.setSource(source);

    if(m_isPlaying){
        m_mediaPlayer.play();
    }
}

void PlayerController::playPause()
{
    m_isPlaying = !m_isPlaying;
    emit isPlayingChanged();

    if(m_isPlaying){
        m_mediaPlayer.play();
    }else{
        m_mediaPlayer.pause();
    }
}

void PlayerController::randomSong()
{
    m_isRandom = !m_isRandom;
    emit isRandomChanged();
}

void PlayerController::activeLoop()
{
    m_isLooping = !m_isLooping;
    emit isLoopingChanged();
}

void PlayerController::loopSong()
{
    if(m_isLooping){
        setCurrentSong(m_audioList[m_audioList.indexOf(m_currentSong)]);
        m_mediaPlayer.play();
    }
}

void PlayerController::addAudio(const QString &audioTile, const QString &audioAuthor, const QUrl &audioImage, const QUrl &audioSource)
{
    beginInsertRows(QModelIndex(), m_audioList.length(), m_audioList.length());

    AudioInfo *audioInfo = new AudioInfo(this);
    audioInfo->setAudioTitle(audioTile);
    audioInfo->setAudioAuthor(audioAuthor);
    audioInfo->setAudioImage(audioImage);
    audioInfo->setAudioSource(audioSource);

    if(m_audioList.isEmpty()){
        setCurrentSong(audioInfo);
    }

    m_audioList << audioInfo;

    endInsertRows();
}

void PlayerController::removeAudio(int index)
{
    if(index>=0 && index<m_audioList.length()){
        beginRemoveRows(QModelIndex(), index, index);

        AudioInfo *removedAudio = m_audioList[index];

        if(removedAudio == currentSong()){
            if(m_audioList.length() > 1) {
                if(index != 0) {
                    setCurrentSong(m_audioList[index - 1]);
                } else {
                    setCurrentSong(m_audioList[index + 1]);
                }
            }else {
                setCurrentSong(nullptr);
            }
        }

        m_audioList.removeAt(index);
        removedAudio->deleteLater();

        endRemoveRows();
    }
}

int PlayerController::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_audioList.length();
}

QVariant PlayerController::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> PlayerController::roleNames() const
{
    QHash<int, QByteArray> result;

    result[AudioTitleRole] = "audioTitle";
    result[AudioAuthorRole] = "audioAuthor";
    result[AudioImageRole] = "audioImage";
    result[AudioSourceRole] = "audioSource";

    return result;
}

int PlayerController::duration()
{
    return m_mediaPlayer.duration()/1000;
}

int PlayerController::currentPosition()
{
    return m_mediaPlayer.position()/1000;
}

void PlayerController::setCurrentPosition(const int &position)
{
    m_mediaPlayer.setPosition(position*1000);
}

void PlayerController::changeVolume(const float &volume)
{
    m_audioOutput->setVolume(volume/100);
}

bool PlayerController::isRandom() const
{
    return m_isRandom;
}

bool PlayerController::isLooping() const
{
    return m_isLooping;
}
