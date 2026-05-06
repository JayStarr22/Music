#include "musicplayer.h"

MusicPlayer::MusicPlayer(QObject *parent)
    : QObject(parent)
{
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
}

MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::play()
{
    mediaPlayer->play();
}

void MusicPlayer::pause()
{
    mediaPlayer->pause();
}

void MusicPlayer::stop()
{
    mediaPlayer->stop();
}

void MusicPlayer::next()
{
    // Implementation for next track
}

void MusicPlayer::previous()
{
    // Implementation for previous track
}

void MusicPlayer::seek(qint64 position)
{
    mediaPlayer->setPosition(position);
}

void MusicPlayer::setVolume(int volume)
{
    audioOutput->setVolume(volume / 100.0);
}

void MusicPlayer::loadTrack(const QString &filePath)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
}
