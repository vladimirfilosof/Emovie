#include "emodetection.h"

#include <iostream>
#include <string>
#include <QDebug>

EmoDetector::EmoDetector()
{

}

QVector<QVector<double>> EmoDetector::detect(QString file)
{
	QString command = "source ~/.virtualenvs/emovie/bin/activate && python3.6 /home/vladimir/Projects/Emovie/src/emo-detection/emotions.py --file ";
	command += file;

	results = popen(command.toLocal8Bit().data(), "r");
	std::string str;
	char buffer[128];
	while (fgets(buffer, 128, results) != nullptr)
	{
		str += buffer;
	}

	int count = 0;

	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == 'n')
			++count;
	}

	QVector<QVector<double>> result(EMOTION_COUNT);

	QVector<char> char_nums(EMOTION_COUNT);
	for (int i = 0; i < EMOTION_COUNT; ++i)
	{
		char_nums[i] = i + '0';
	}

	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == 'n')
		{
			for (int j = 0; j < EMOTION_COUNT; ++j)
			{
				result[j].append(-1);
			}
		}
		for (int j = 0; j < EMOTION_COUNT; ++j)
		{
			if (str[i] == char_nums[j])
			{
				result[j][result[j].size() - 1] = j;
			}
		}
	}

	return result;
}
