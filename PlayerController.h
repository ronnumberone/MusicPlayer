#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QMediaPlayer>
#include <QAbstractListModel>

class AudioInfo;

class PlayerController : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(AudioInfo* currentSong READ currentSong WRITE setCurrentSong NOTIFY currentSongChanged FINAL)
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged FINAL)
    Q_PROPERTY(bool isRandom READ isRandom NOTIFY isRandomChanged FINAL)
    Q_PROPERTY(bool isLooping READ isLooping NOTIFY isLoopingChanged FINAL)

public:
    enum Role{
        AudioTitleRole=Qt::UserRole+1,
        AudioAuthorRole,
        AudioImageRole,
        AudioSourceRole
    };
    explicit PlayerController(QObject *parent = nullptr);

    AudioInfo *currentSong() const;
    void setCurrentSong(AudioInfo *newCurrentSong);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    bool isPlaying() const;

    bool isRandom() const;

    bool isLooping() const;

public slots:
    void switchToNextSong();
    void switchToPreviousSong();
    void switchToSongByIndex(int index);
    void changeAudioSource(const QUrl &source);
    void playPause();
    void randomSong();
    void activeLoop();
    void loopSong();
    void addAudio(const QString &audioTile, const QString &audioAuthor, const QUrl &audioImage, const QUrl &audioSource = QUrl());
    void removeAudio(int index);
    int duration();
    int currentPosition();
    void setCurrentPosition(const int &position);
    void changeVolume(const float &volume);

signals:
    void currentSongChanged();

    void isPlayingChanged();

    void isRandomChanged();

    void isLoopingChanged();

private:
    AudioInfo *m_currentSong = nullptr;
    bool m_isPlaying = false;
    QAudioOutput *m_audioOutput = nullptr;
    QList<AudioInfo*> m_audioList;
    QList<AudioInfo*> m_randomSongList;
    QMediaPlayer m_mediaPlayer;
    bool m_isRandom = false;
    bool m_isLooping = false;
};

#endif // PLAYERCONTROLLER_H
