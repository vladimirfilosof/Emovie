#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QMediaPlayer>

class Player: public QVideoWidget
{
	Q_OBJECT

public:
	Player(QWidget *parent = nullptr);
	virtual ~Player(){}

    QMediaPlaylist *playlist;
    QMediaPlayer *player;
	QVideoWidget *videoWidget;
	int duration;
public slots:
	void Play();
	void Pause();
	void Stop();
	void setPos(int pos);
	void setDuration(qint64 duration);
	void setVideo(QString filename);
	void posChanged(qint64 pos);

signals:
	void duration_changed(int duration);
	void position_changed(int pos);
};

#endif // PLAYER_H
