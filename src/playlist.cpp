#include "playlist.h"

Playlist::Playlist(QObject *parent)
    : QObject(parent)
{
}

Playlist::~Playlist()
{
}

void Playlist::addTrack(const PlaylistTrack &track)
{
    tracks.append(track);
    emit trackAdded(track);
    emit playlistChanged();
}

void Playlist::removeTrack(int index)
{
    if (index >= 0 && index < tracks.size()) {
        tracks.removeAt(index);
        emit trackRemoved(index);
        emit playlistChanged();
    }
}

void Playlist::clearPlaylist()
{
    tracks.clear();
    emit playlistChanged();
}

PlaylistTrack Playlist::getTrack(int index) const
{
    if (index >= 0 && index < tracks.size()) {
        return tracks.at(index);
    }
    return PlaylistTrack();
}

int Playlist::getTrackCount() const
{
    return tracks.size();
}

QList<PlaylistTrack> Playlist::getTracks() const
{
    return tracks;
}

void Playlist::savePlaylist(const QString &filePath)
{
    // TODO: Implement playlist save functionality (M3U format)
}

void Playlist::loadPlaylist(const QString &filePath)
{
    // TODO: Implement playlist load functionality (M3U format)
}
