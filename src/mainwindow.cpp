#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QTableWidget>
#include <QListWidget>
#include <QSplitter>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Music Player");
    setGeometry(100, 100, 1200, 700);

    // Initialize core components
    musicPlayer = new MusicPlayer(this);
    libraryManager = new LibraryManager(this);
    currentPlaylist = new Playlist(this);

    setupUI();
    connectSignals();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // ===== LEFT SIDEBAR =====
    QWidget *leftPanel = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    QLabel *libraryLabel = new QLabel("Library");
    libraryWidget = new QListWidget();
    libraryWidget->addItems({"All Music", "Artists", "Albums", "Genres", "Playlists"});

    QLabel *playlistLabel = new QLabel("Playlists");
    playlistWidget = new QListWidget();
    playlistWidget->addItems({"Favorites", "Recent", "My Playlist 1"});

    leftLayout->addWidget(libraryLabel);
    leftLayout->addWidget(libraryWidget);
    leftLayout->addSpacing(20);
    leftLayout->addWidget(playlistLabel);
    leftLayout->addWidget(playlistWidget);

    // ===== CENTER PANEL =====
    QWidget *centerPanel = new QWidget();
    QVBoxLayout *centerLayout = new QVBoxLayout(centerPanel);

    albumArtLabel = new QLabel();
    albumArtLabel->setMinimumSize(300, 300);
    albumArtLabel->setStyleSheet("background-color: #444; border: 1px solid #666;");
    albumArtLabel->setAlignment(Qt::AlignCenter);
    albumArtLabel->setText("Album Art");

    trackTableWidget = new QTableWidget();
    trackTableWidget->setColumnCount(4);
    trackTableWidget->setHorizontalHeaderLabels({"Title", "Artist", "Album", "Duration"});
    trackTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    centerLayout->addWidget(albumArtLabel);
    centerLayout->addWidget(trackTableWidget);

    // ===== RIGHT SIDEBAR =====
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    QLabel *queueLabel = new QLabel("Queue");
    queueWidget = new QListWidget();
    queueWidget->addItems({"Track 1", "Track 2", "Track 3"});

    QLabel *infoLabel = new QLabel("Info");
    artistInfoLabel = new QLabel("Artist Information");
    lyricsLabel = new QLabel("Lyrics");

    rightLayout->addWidget(queueLabel);
    rightLayout->addWidget(queueWidget);
    rightLayout->addWidget(infoLabel);
    rightLayout->addWidget(artistInfoLabel);
    rightLayout->addWidget(lyricsLabel);

    // ===== SPLITTER FOR RESIZABLE PANELS =====
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(leftPanel);
    splitter->addWidget(centerPanel);
    splitter->addWidget(rightPanel);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);
    splitter->setStretchFactor(2, 1);

    mainLayout->addWidget(splitter);

    // ===== BOTTOM PANEL (PLAYBACK CONTROLS) =====
    QWidget *bottomPanel = new QWidget();
    QVBoxLayout *bottomLayout = new QVBoxLayout(bottomPanel);

    // Progress bar
    progressSlider = new QSlider(Qt::Horizontal);
    currentTimeLabel = new QLabel("0:00");
    totalTimeLabel = new QLabel("0:00");

    QHBoxLayout *progressLayout = new QHBoxLayout();
    progressLayout->addWidget(currentTimeLabel);
    progressLayout->addWidget(progressSlider);
    progressLayout->addWidget(totalTimeLabel);

    // Control buttons
    playButton = new QPushButton("▶ Play");
    pauseButton = new QPushButton("⏸ Pause");
    previousButton = new QPushButton("⏮ Previous");
    nextButton = new QPushButton("⏭ Next");

    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addWidget(previousButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(pauseButton);
    controlLayout->addWidget(nextButton);
    controlLayout->addStretch();

    // Volume control
    QLabel *volumeLabel = new QLabel("Volume:");
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(70);
    volumeSlider->setMaximumWidth(150);

    QHBoxLayout *volumeLayout = new QHBoxLayout();
    volumeLayout->addStretch();
    volumeLayout->addWidget(volumeLabel);
    volumeLayout->addWidget(volumeSlider);

    bottomLayout->addLayout(progressLayout);
    bottomLayout->addLayout(controlLayout);
    bottomLayout->addLayout(volumeLayout);

    // Add bottom panel to main layout
    mainLayout->setDirection(QBoxLayout::TopToBottom);
    QMainWindow::centralWidget()->setLayout(mainLayout);

    // Create a container for everything
    QWidget *container = new QWidget();
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->addWidget(splitter);
    containerLayout->addWidget(bottomPanel);
    setCentralWidget(container);
}

void MainWindow::connectSignals()
{
    connect(playButton, &QPushButton::clicked, this, &MainWindow::onPlayClicked);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseClicked);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(previousButton, &QPushButton::clicked, this, &MainWindow::onPreviousClicked);
    connect(volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);

    connect(musicPlayer, &MusicPlayer::positionChanged, this, &MainWindow::onPositionChanged);
    connect(musicPlayer, &MusicPlayer::durationChanged, this, &MainWindow::onDurationChanged);

    connect(libraryWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        onLibraryItemSelected(item->text());
    });

    connect(trackTableWidget, &QTableWidget::cellDoubleClicked, this, &MainWindow::onTrackSelected);
}

void MainWindow::onPlayClicked()
{
    musicPlayer->play();
}

void MainWindow::onPauseClicked()
{
    musicPlayer->pause();
}

void MainWindow::onNextClicked()
{
    musicPlayer->next();
}

void MainWindow::onPreviousClicked()
{
    musicPlayer->previous();
}

void MainWindow::onVolumeChanged(int value)
{
    musicPlayer->setVolume(value);
}

void MainWindow::onPositionChanged(qint64 position)
{
    progressSlider->blockSignals(true);
    progressSlider->setValue(position / 1000);
    progressSlider->blockSignals(false);

    int seconds = (position / 1000) % 60;
    int minutes = (position / 60000) % 60;
    currentTimeLabel->setText(QString::number(minutes) + ":" + QString::number(seconds).rightJustified(2, '0'));
}

void MainWindow::onDurationChanged(qint64 duration)
{
    progressSlider->setMaximum(duration / 1000);

    int seconds = (duration / 1000) % 60;
    int minutes = (duration / 60000) % 60;
    totalTimeLabel->setText(QString::number(minutes) + ":" + QString::number(seconds).rightJustified(2, '0'));
}

void MainWindow::onLibraryItemSelected(const QString &item)
{
    // TODO: Load library items based on selection
}

void MainWindow::onTrackSelected(int row)
{
    musicPlayer->playTrack(row);
}

void MainWindow::updateTrackInfo()
{
    // TODO: Update track information display
}
