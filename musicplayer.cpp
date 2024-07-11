#include "MusicPlayer.h"
#include <QDebug>

MusicPlayer::MusicPlayer(QObject *parent) : QObject(parent)
{
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
}

void MusicPlayer::playMusic(const QString &filePath)
{
    QUrl fileUrl = QUrl::fromLocalFile(filePath);
    qDebug() << "Trying to play music from: " << filePath;
    qDebug() << "Resolved URL: " << fileUrl.toString();
    mediaPlayer->setSource(fileUrl);
    audioOutput->setVolume(50); // Adjust the volume as needed
    mediaPlayer->play();

    if (mediaPlayer->error() != QMediaPlayer::NoError) {
        qDebug() << "Error playing music:" << mediaPlayer->errorString();
    } else {
        qDebug() << "Music is playing...";
    }
}
