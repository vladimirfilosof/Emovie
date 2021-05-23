#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QVector>
#include <QSlider>
#include <QStyle>
#include "player.h"
#include "qcustomplot.h"
#include "emodetection.h"
//#include "timeline.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QPushButton *video_load_btn;
	QLineEdit *video_title;
	QString file_title;
	Player *video_player;
	QCustomPlot *plot;
	QSlider *timeline;
	EmoDetector Emo_detector;
	QVector<QVector<double>> emo_data;
	void setup_plot();
	void emo_procent();


private slots:
	void load_video();
	void set_duration_video(int duration);
	void test(int pos);

};
#endif // MAINWINDOW_H
