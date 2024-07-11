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
    void playMusic(const QString &filePath);

private:
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
};

#endif // MUSICPLAYER_H
