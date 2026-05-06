#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>
#include <QLabel>
#include <QListWidget>
#include <QTableWidget>
#include "musicplayer.h"
#include "librarymanager.h"
#include "playlist.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPlayClicked();
    void onPauseClicked();
    void onNextClicked();
    void onPreviousClicked();
    void onVolumeChanged(int value);
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 duration);
    void onLibraryItemSelected(const QString &artist);
    void onTrackSelected(int row);

private:
    void setupUI();
    void connectSignals();
    void updateTrackInfo();

    // UI Components - Left Sidebar
    QListWidget *libraryWidget;
    QListWidget *playlistWidget;

    // Center Panel
    QLabel *albumArtLabel;
    QTableWidget *trackTableWidget;

    // Right Sidebar
    QListWidget *queueWidget;
    QLabel *lyricsLabel;
    QLabel *artistInfoLabel;

    // Bottom Panel
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QSlider *progressSlider;
    QSlider *volumeSlider;
    QLabel *currentTimeLabel;
    QLabel *totalTimeLabel;

    // Core functionality
    MusicPlayer *musicPlayer;
    LibraryManager *libraryManager;
    Playlist *currentPlaylist;
};

#endif // MAINWINDOW_H
