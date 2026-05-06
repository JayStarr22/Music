#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>

struct AudioFile {
    QString filePath;
    QString title;
    QString artist;
    QString album;
    QString genre;
    int duration;
};

class LibraryManager : public QObject
{
    Q_OBJECT

public:
    explicit LibraryManager(QObject *parent = nullptr);
    ~LibraryManager();

    void scanDirectory(const QString &directoryPath);
    QList<AudioFile> getLibrary() const;
    QList<AudioFile> searchByArtist(const QString &artist) const;
    QList<AudioFile> searchByAlbum(const QString &album) const;

signals:
    void libraryUpdated();
    void scanProgress(int current, int total);

private:
    void scanDirectoryRecursive(const QString &directoryPath);
    AudioFile readMetadata(const QString &filePath);

    QList<AudioFile> library;
};

#endif // LIBRARYMANAGER_H
