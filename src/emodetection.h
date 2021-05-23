#ifndef EMODETECTION_H
#define EMODETECTION_H

#include <QVector>
#include <QString>
#include <cstdio>


class EmoDetector
{
public:
	EmoDetector();
	QVector<QVector<double>> detect(QString file);
	const int EMOTION_COUNT = 7;
private:
	FILE *results;
};

#endif // EMODETECTION_H
