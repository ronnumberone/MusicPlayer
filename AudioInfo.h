#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QObject>
#include <QUrl>
#include <qqml.h>

class AudioInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int audioIndex READ audioIndex WRITE setAudioIndex NOTIFY audioIndexChanged FINAL)
    Q_PROPERTY(QString audioTitle READ audioTitle WRITE setAudioTitle NOTIFY audioTitleChanged FINAL)
    Q_PROPERTY(QString audioAuthor READ audioAuthor WRITE setAudioAuthor NOTIFY audioAuthorChanged FINAL)
    Q_PROPERTY(QUrl audioImage READ audioImage WRITE setAudioImage NOTIFY audioImageChanged FINAL)
    Q_PROPERTY(QUrl audioSource READ audioSource WRITE setAudioSource NOTIFY audioSourceChanged FINAL)
    Q_PROPERTY(int audioDuration READ audioDuration WRITE setAudioDuration NOTIFY audioDurationChanged FINAL)

public:
    explicit AudioInfo(QObject *parent = nullptr);
    QString audioTitle() const;
    void setAudioTitle(QString newAudioTitle);

    int audioIndex() const;
    void setAudioIndex(int newAudioIndex);

    QString audioAuthor() const;
    void setAudioAuthor(QString newAudioAuthor);

    QUrl audioImage() const;
    void setAudioImage(const QUrl &newAudioImage);

    QUrl audioSource() const;
    void setAudioSource(const QUrl &newAudioSource);

    int audioDuration() const;
    void setAudioDuration(int newAudioDuration);

signals:
    void audioTitleChanged();

    void audioIndexChanged();

    void audioAuthorChanged();

    void audioImageChanged();

    void audioSourceChanged();

    void audioDurationChanged();

private:
    QString m_audioTitle;
    int m_audioIndex;
    QString m_audioAuthor;
    QUrl m_audioImage;
    QUrl m_audioSource;
    int m_audioDuration;
};

#endif // AUDIOINFO_H
