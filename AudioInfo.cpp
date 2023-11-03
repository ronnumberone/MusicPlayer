#include "AudioInfo.h"

AudioInfo::AudioInfo(QObject *parent)
    :QObject(parent)
{

}

int AudioInfo::audioIndex() const
{
    return m_audioIndex;
}

void AudioInfo::setAudioIndex(int newAudioIndex)
{
    if (m_audioIndex == newAudioIndex)
        return;
    m_audioIndex = newAudioIndex;
    emit audioIndexChanged();
}

QString AudioInfo::audioTitle() const
{
    return m_audioTitle;
}

void AudioInfo::setAudioTitle(QString newAudioTitle)
{
    if (m_audioTitle == newAudioTitle)
        return;
    m_audioTitle = newAudioTitle;
    emit audioTitleChanged();
}

QString AudioInfo::audioAuthor() const
{
    return m_audioAuthor;
}

void AudioInfo::setAudioAuthor(QString newAudioAuthor)
{
    if (m_audioAuthor == newAudioAuthor)
        return;
    m_audioAuthor = newAudioAuthor;
    emit audioAuthorChanged();
}

QUrl AudioInfo::audioImage() const
{
    return m_audioImage;
}

void AudioInfo::setAudioImage(const QUrl &newAudioImage)
{
    if (m_audioImage == newAudioImage)
        return;
    m_audioImage = newAudioImage;
    emit audioImageChanged();
}

QUrl AudioInfo::audioSource() const
{
    return m_audioSource;
}

void AudioInfo::setAudioSource(const QUrl &newAudioSource)
{
    if (m_audioSource == newAudioSource)
        return;
    m_audioSource = newAudioSource;
    emit audioSourceChanged();
}

int AudioInfo::audioDuration() const
{
    return m_audioDuration;
}

void AudioInfo::setAudioDuration(int newAudioDuration)
{
    if (m_audioDuration == newAudioDuration)
        return;
    m_audioDuration = newAudioDuration;
    emit audioDurationChanged();
}
