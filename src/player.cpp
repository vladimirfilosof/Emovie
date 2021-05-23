#include "player.h"
#include <iostream>

Player::Player(QWidget *parent)
{
	player = new QMediaPlayer();
	player->setVideoOutput(this);
	player->setVolume(0);
	connect(player, &QMediaPlayer::durationChanged, this, &Player::setDuration);
	connect(player, &QMediaPlayer::positionChanged, this, &Player::posChanged);
}

void Player::Play()
{
    player->play();
}
void Player::Pause()
{
    player->pause();
}
void Player::Stop()
{
    player->stop();
}

void Player::setPos(int pos)
{

	player->setPosition(pos);
}

void Player::setDuration(qint64 duration)
{
	this->duration = duration;
	emit duration_changed(duration);
}

void Player::setVideo(QString filename)
{
	player->setMedia(QUrl::fromLocalFile(filename));
}

void Player::posChanged(qint64 pos)
{
	emit position_changed(pos);
}
