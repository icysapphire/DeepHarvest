#include "MainScreen.h"
#include "GameView.h"
#include "GameEngine.h"
#include <qt/QtCore/QString>
#include <qt/QtWidgets/QLabel>
#include <qt/QtWidgets/QPushButton>
#include <qt/QtWidgets/QVBoxLayout>

MainScreen::MainScreen(QWidget *parent) {
	QWidget *window = new QWidget(this);
	window->setObjectName("window");
	window->setStyleSheet("#window{background-image:url(:/images/sky.jpg);width:800px;} QLabel{padding-top:20px; padding-bottom:20px;font-size:18px;} QPushButton{font-size:18px;}");
	
	setWindowTitle("DeepHarvest");
	QLabel * title = new QLabel("<h1>DeepHarvest</h1>",this);
	QLabel * how_to = new QLabel(this);

	QString how_to_txt(QString("Welcome to a very simple catch game. <br />The aim is to move the boy in order to catch strawberries and avoid holes. <br /> You have 50 moves to be done in no more than 15 seconds, then the grid will be restored to initial state and an AI agent built upon a deep Q-network will play the game. <br />Move with <u>arrow keys</u>."));
	QString Game1_txt("<h2>Game #1</h2>- Bonuses and holes are of fixed weight 1 and -1.");
	QString Game2_txt("<h2>Game #2</h2>- Bonuses are of random weights between 16 and 64, their sum is 100. <br />Falling down a hole will make you loose 30% of harvested strawberries.");

	how_to->setText(how_to_txt);
	how_to->setAlignment(Qt::AlignHCenter);
	title->setAlignment(Qt::AlignHCenter);
	
	QPushButton * play1_btn = new QPushButton("Play #1",this);
	QPushButton * play2_btn = new QPushButton("Play #2",this);
	
	QVBoxLayout * layout = new QVBoxLayout(this);
	
	layout->addWidget(title);
	layout->addWidget(how_to);
	layout->addWidget(new QLabel(Game1_txt,this));
	layout->addWidget(play1_btn);
	layout->addWidget(new QLabel(Game2_txt,this));
	layout->addWidget(play2_btn);
	window->setMaximumWidth(800);
	window->setMaximumHeight(550);
	window->setLayout(layout);

	connect(play1_btn,SIGNAL(clicked()),this,SLOT(play_1()));
	connect(play2_btn,SIGNAL(clicked()),this,SLOT(play_2()));
	setAutoFillBackground(true);
}

void MainScreen::play(const int mode) {
	game_v = new GameView(mode);
	//game->showFullScreen(); // show full screen
	game_v->setFixedSize(1280,720);
	game_v->showNormal();
	game_v->SetPath(utility::get_working_directory());

	//close window
	close();
}
