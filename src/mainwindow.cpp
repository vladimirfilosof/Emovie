#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	video_load_btn = ui->video_load_btn;
	video_title = ui->video_title;
	video_title->setReadOnly(true);

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
}
