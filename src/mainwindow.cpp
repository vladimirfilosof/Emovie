#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDebug>

#include <cmath>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	video_load_btn = ui->video_load_btn;
	video_title = ui->video_title;
	video_title->setReadOnly(true);

	video_player = ui->player;
	QPushButton *play_btn = ui->video_play_btn;
	connect(play_btn, &QPushButton::clicked, video_player, &Player::Play);
	QPushButton *stop_btn = ui->video_pause_btn;
	connect(stop_btn, &QPushButton::clicked, video_player, &Player::Pause);

	setup_plot();

	timeline = ui->horizontalSlider;
	timeline->setMinimum(0);
	timeline->setMaximum(0);

	connect(timeline, SIGNAL(sliderMoved(int)), video_player, SLOT(setPos(int)));
	connect(video_player, SIGNAL(position_changed(int)), timeline, SLOT(setValue(int)));

	connect(video_player, &Player::duration_changed, this, &MainWindow::set_duration_video);
	connect(video_load_btn, &QPushButton::clicked, this, &MainWindow::load_video);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::load_video()
{
	file_title = QFileDialog::getOpenFileName();
	video_title->setText(file_title);
	video_player->setVideo(file_title);
	timeline->setMaximum(video_player->duration);


	emo_data = Emo_detector.detect(file_title);

	int count = emo_data[0].size();

	QVector<double> X(count);
	for (int i = 0; i < count; ++i)
	{
		X[i] = i;
	}

	for (int i = 0; i < Emo_detector.EMOTION_COUNT; ++i)
	{
		plot->graph(i)->setData(X, emo_data[i]);
	}

	plot->xAxis->setRange(0, count);
	plot->replot();

	emo_procent();
}

void MainWindow::set_duration_video(int duration)
{
	timeline->setMaximum(duration);
}

void MainWindow::test(int pos)
{
	timeline->setValue(pos);
}

void MainWindow::setup_plot()
{
	plot = ui->plot;

	for (int i = 0; i < Emo_detector.EMOTION_COUNT; ++i)
		plot->addGraph();


	QSharedPointer<QCPAxisTickerText> tickets(new QCPAxisTickerText);
	tickets->addTick(0, "Angry");
	tickets->addTick(1, "Disgusted");
	tickets->addTick(2, "Fearful");
	tickets->addTick(3, "Happy");
	tickets->addTick(4, "Neutral");
	tickets->addTick(5, "Sad");
	tickets->addTick(6, "Surprised");

	for (int i = 0; i < Emo_detector.EMOTION_COUNT; ++i)
	{
		//убираем линии
		plot->graph(i)->setLineStyle(QCPGraph::lsNone);
		//формируем вид точек
		plot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 4));
	}
	plot->graph(0)->setPen(QPen(QColor("red")));
	plot->graph(1)->setPen(QPen(QColor("green")));
	plot->graph(2)->setPen(QPen(QColor("darkCyan")));
	plot->graph(3)->setPen(QPen(QColor("yellow")));
	plot->graph(4)->setPen(QPen(QColor("gray")));
	plot->graph(5)->setPen(QPen(QColor("blue")));
	plot->graph(6)->setPen(QPen(QColor("cyan")));


	plot->yAxis->setRange(-0.5, 6.5);
	plot->yAxis->setTicker(tickets);
	plot->xAxis->setRange(0, 0);
}

void MainWindow::emo_procent()
{
	QVector<double> procents(Emo_detector.EMOTION_COUNT);
	for (int i = 0; i < Emo_detector.EMOTION_COUNT; ++i)
	{
		double count = 0;
		for (int j = 0; j < emo_data[i].size(); ++j)
		{
			if (emo_data[i][j] != -1)
				++count;
		}
		procents[i] = count / emo_data[i].size() * 100;
	}
	std::string str_procents[Emo_detector.EMOTION_COUNT];

	for (int i = 0; i < Emo_detector.EMOTION_COUNT; ++i)
	{
		str_procents[i] = std::to_string(round(procents[i] * 100) / 100);
		str_procents[i].erase(str_procents[i].find_last_not_of('0') + 1, std::string::npos);
		str_procents[i].erase(str_procents[i].find_last_not_of(',') + 1, std::string::npos);
		str_procents[i] += '%';
	}

	ui->angry_line->setText(str_procents[0].c_str());
	ui->disgusted_line->setText(str_procents[1].c_str());
	ui->fearful_line->setText(str_procents[2].c_str());
	ui->happy_line->setText(str_procents[3].c_str());
	ui->neutral_line->setText(str_procents[4].c_str());
	ui->sad_line->setText(str_procents[5].c_str());
	ui->surprised_line->setText(str_procents[6].c_str());
}
