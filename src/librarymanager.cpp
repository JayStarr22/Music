#include "librarymanager.h"
#include <QDirIterator>
#include <QFileInfo>
#include <QMediaMetaData>

LibraryManager::LibraryManager(QObject *parent)
    : QObject(parent)
{
}

LibraryManager::~LibraryManager()
{
}

void LibraryManager::scanLibrary(const QString &path)
{
    tracks.clear();
    artists.clear();
    albums.clear();
    genres.clear();

    QDirIterator it(path, QStringList() << "*.mp3" << "*.flac" << "*.ogg" << "*.wav", 
                    QDir::Files, QDirIterator::Subdirectories);

    int count = 0;
    while (it.hasNext()) {
        QString filePath = it.next();
        Track track;
        track.filePath = filePath;
        track.title = QFileInfo(filePath).baseName();
        
        loadTrackMetadata(filePath, track);
        
        tracks.append(track);

        if (!artists.contains(track.artist)) {
            artists.append(track.artist);
        }
        if (!albums.contains(track.album)) {
            albums.append(track.album);
        }

        emit scanProgress(++count, 0);
    }

    emit libraryUpdated();
}

void LibraryManager::loadTrackMetadata(const QString &filePath, Track &track)
{
    // TODO: Use QMediaPlayer or external library to read metadata
    // For now, use filename as title
    track.artist = "Unknown Artist";
    track.album = "Unknown Album";
    track.duration = 0;
}

QList<Track> LibraryManager::getTracksByArtist(const QString &artist)
{
    QList<Track> result;
    for (const Track &track : tracks) {
        if (track.artist == artist) {
            result.append(track);
        }
    }
    return result;
}

QList<Track> LibraryManager::getTracksByAlbum(const QString &album)
{
    QList<Track> result;
    for (const Track &track : tracks) {
        if (track.album == album) {
            result.append(track);
        }
    }
    return result;
}

QList<Track> LibraryManager::getTracksByGenre(const QString &genre)
{
    QList<Track> result;
    // TODO: Implement genre filtering
    return result;
}

QList<Track> LibraryManager::getAllTracks()
{
    return tracks;
}

QStringList LibraryManager::getArtists()
{
    return artists;
}

QStringList LibraryManager::getAlbums()
{
    return albums;
}

QStringList LibraryManager::getGenres()
{
    return genres;
}
