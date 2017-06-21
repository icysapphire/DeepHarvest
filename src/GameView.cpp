#include "GameView.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Bonus.h"
#include "Hole.h"
#include <qt/QtWidgets/QGraphicsScene>
#include <qt/QtGui/QKeyEvent>
#include <qt/QtCore/QLineF>
#include <qt/QtCore/QPointF>
#include <qt/QtGui/QImage>
#include <qt/QtGui/QPen>
#include <qt/QtCore/QString>
#include <qt/QtCore/QTimer>
#include <stdlib.h>
#include <string>

const QString GameView::human_turn = "<h1>It's human turn.</h1>";
const QString GameView::initial_human_score_tooltip = "Human score: <b style='color:#06C; font-size:20px;'>0</b>, Moves:<b>0/50</b>";
const QString GameView::initial_ai_score_tooltip = "AI score: <b style='color:#06C; font-size:20px;'>0</b>, Moves:<b>0/50</b>";
const QString GameView::ai_turn = "<h1>Now it's AI turn...</h1>";
const string GameView::seconds_tooltip_text="<h1 style='color:red'>%1% seconds</h1>";
const string GameView::score_change_positive_text="<h1 style='color:green;'>+%1%</h1>";
const string GameView::score_change_negative_text="<h1 style='color:red;'>%1%</h1>";
const int GameView::rect_margin = 20;
const int GameView::seconds_turn = 15;


GameView::GameView(const int mode_, QWidget *parent): QGraphicsView(parent), game_eng(mode_,9,9), seconds(0) {
	// add scene
	scene = new QGraphicsScene(this);
	
	QPen whitepen(Qt::white);
    whitepen.setWidth(5);

    scene->addRect(rect_margin,rect_margin,64*game_eng.GetWidth(),64*game_eng.GetHeight(), whitepen);
    whitepen.setWidth(0.4f);
    for(int i=0; i<9; i++){
    scene->addLine(rect_margin+i*64,rect_margin,rect_margin+i*64,rect_margin+game_eng.GetHeight()*64, whitepen);
    scene->addLine(rect_margin,rect_margin+i*64,rect_margin+game_eng.GetWidth()*64,rect_margin+i*64, whitepen);
	}

	// set scene background
	scene->setSceneRect(0,0,width(),height());
	QImage * img = new QImage(":/images/grass2.jpg");
	QBrush bg_brush(*img);
	scene->setBackgroundBrush(bg_brush);

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);

	// set the scene and the part of the scene to view (the whole thing in this case)
	setScene(scene);
	setSceneRect(scene->sceneRect());

	// disable scrollbars for the view
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setWindowTitle("DeepHarvest");

	turn_tooltip = new TextItem(human_turn,680,100);
	turn_tooltip->setZValue(1);
	scene->addItem(turn_tooltip);

	human_tooltip = new TextItem(initial_human_score_tooltip,700,200, QColor("#f5deef"));
	scene->addItem(human_tooltip);

	ai_tooltip = new TextItem(initial_ai_score_tooltip,700,300, QColor("#deeff5"));
	scene->addItem(ai_tooltip);
	
	seconds_tooltip = new TextItem("",-200,500, QColor("white"));
	scene->addItem(seconds_tooltip);
	
	change_tooltip = new TextItem("",700,500, QColor("#FFFFFF"));
	change_tooltip->hide();
	scene->addItem(change_tooltip);
	
	game_eng.PopulateGrid(scene);
	game_eng.Play();
	
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, [this](){
		this->seconds++;
		seconds_tooltip->setHtml(utility::qstring_placeholder(seconds_tooltip_text, seconds_turn-seconds));
		if(this->seconds >= seconds_turn) {this->timer->stop(); if(game_eng.GetRound()==0) this->PassToAI();}
    });  
    
   timer->setInterval(1000);
   ResetTimer();


}
void GameView::ResetTimer(){
	seconds = 0;
	seconds_tooltip->show();
	seconds_tooltip->setHtml(utility::qstring_placeholder(seconds_tooltip_text, seconds_turn));
	timer->start(); 
}
void GameView::FlashScoreChange(const float delta) {
	auto score_change = change_tooltip;
	
	if(delta>=0) score_change->setHtml(utility::qstring_placeholder(score_change_positive_text, (int)delta));
	else score_change->setHtml(utility::qstring_placeholder(score_change_negative_text, (int)delta));
	score_change->show();
	qApp->processEvents();
	std::this_thread::sleep_for(std::chrono::milliseconds(250));
	score_change->hide();
	qApp->processEvents();
}

void GameView::SetPlayerTooltipText(const QString str){
	if(game_eng.GetRound()==0) human_tooltip->setHtml(str);
	else ai_tooltip->setHtml(str);
}

void GameView::PassToAI() {
	timer->stop();
	seconds_tooltip->hide();
	
	float human_score = game_eng.GetScore();
	turn_tooltip->setHtml(ai_turn);
	turn_tooltip->placeIt(250, 300);
	qApp->processEvents();
	
	RestoreGrid();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	turn_tooltip->placeIt(680, 100);
	
	// let AI play
	game_eng.Play();
	
	float ai_score = game_eng.GetScore();
	
	conclusion_tooltip = new TextItem("",-265,200,"#eff5de");

	if(human_score==ai_score) 
	conclusion_tooltip->setHtml("<h2>Same score!</h2>");
	else
		if (human_score > ai_score)
			conclusion_tooltip->setHtml("<h2>You won!</h2>");
		else 
			conclusion_tooltip->setHtml("<h2>AI won!</h2>");
	
	conclusion_tooltip ->setHtml(conclusion_tooltip->toHtml() + " Press ESC to quit the game.<br />Press SPACE to play a new match.");
	scene->addItem(conclusion_tooltip);

}

void GameView::PlayAgain(){
				
		// Reset tooltips and destroy conclusion_tooltip
		turn_tooltip->setHtml(human_turn);
		human_tooltip->setHtml(initial_human_score_tooltip);
		ai_tooltip->setHtml(initial_ai_score_tooltip);
		
		
		if(conclusion_tooltip != nullptr){
			scene->removeItem(conclusion_tooltip);
			delete conclusion_tooltip;
			conclusion_tooltip = nullptr;
		}

		game_eng.PopulateGrid(scene);
		ResetTimer();
		
		game_eng.Play();
}
void GameView::keyPressEvent(QKeyEvent* event) {
	// Close when pressing ESC
	if (event->key() == Qt::Key_Escape)
		close();
	// Play new match when pressing ESC
	else if (event->key() == Qt::Key_Space && conclusion_tooltip != nullptr)
		PlayAgain();

	// Otherwise, pass keyboard event to scene
	else QGraphicsView::keyPressEvent(event);




}
