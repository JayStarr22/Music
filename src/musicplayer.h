#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class MusicPlayer : public QObject
{
    Q_OBJECT

public:
    explicit MusicPlayer(QObject *parent = nullptr);
    ~MusicPlayer();

    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void setVolume(int volume);
    void setPosition(qint64 position);
    void loadTrack(const QString &filePath);

signals:
    void trackChanged(const QString &title, const QString &artist);
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void stateChanged(QMediaPlayer::PlaybackState state);

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);

private:
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
};

#endif // MUSICPLAYER_H
