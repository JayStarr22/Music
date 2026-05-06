#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QString>
#include <QStringList>

class Playlist : public QObject
{
    Q_OBJECT

public:
    explicit Playlist(QObject *parent = nullptr);
    ~Playlist();

    void addTrack(const QString &filePath);
    void removeTrack(int index);
    void clear();
    QString getCurrentTrack() const;
    QString getTrackAt(int index) const;
    int getTrackCount() const;
    int getCurrentIndex() const;
    void setCurrentIndex(int index);

signals:
    void playlistChanged();
    void currentTrackChanged(int index);

private:
    QStringList tracks;
    int currentIndex = 0;
};

#endif // PLAYLIST_H
