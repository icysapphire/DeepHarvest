#ifndef GAMEVIEW_H
#define GAMEVIEW_H


#include "GameEngine.h"
#include "TextItem.h"
#include "utility.h"
#include <qt/QtWidgets/QGraphicsView>

class GameView;
extern GameView * game_v;
class Player;

class GameView: public QGraphicsView {
public:
	GameView(const int mode_, QWidget * parent=0);
	
	/**
	* @brief stores working directory
	* @param path is the working directory path
	*/
	void SetPath(const std::string path_){
		path = path_;
	}
	
	std::string GetPath(){return path;}
	
	/**
	* @brief resets the game environment in order to let AI agent play
	*/
	void PassToAI();
	
	void keyPressEvent(QKeyEvent* event);
	
	/**
	* @brief displays score change as consequence of a move
	* @param delta is the score variation
	*/
	void FlashScoreChange(const float delta);

	/**
	* @brief displays score change as consequence of a move
	* @param delta is the score variation
	*/
	void SetPlayerTooltipText(const QString str);
	
	static const int rect_margin;
	static const int seconds_turn;
	
protected:
	inline void RestoreGrid() {
		game_eng.PopulateGrid(scene,true);
	}
	void ResetTimer();
	void PlayAgain();
	
	
	static const QString human_turn;
	static const QString ai_turn;
	static const QString initial_human_score_tooltip;
	static const QString initial_ai_score_tooltip;
	static const string seconds_tooltip_text;
	static const string score_change_positive_text;
	static const string score_change_negative_text;
	
	
	TextItem* turn_tooltip = nullptr;
	TextItem* human_tooltip = nullptr;
	TextItem* ai_tooltip = nullptr;
	TextItem* conclusion_tooltip = nullptr;
	TextItem* change_tooltip = nullptr;
	TextItem* seconds_tooltip = nullptr;
	
	string path; // working directory
	
	QGraphicsScene * scene = nullptr;
	GameEngine game_eng;
	
	QTimer *timer; int seconds;
	

};

#endif // GAMEVIEW_H
