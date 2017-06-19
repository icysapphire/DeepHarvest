#ifndef HPLAYER_H
#define HPLAYER_H

#include "Player.h"
#include "GameEngine.h"

class HumanPlayer: public Player {
public:
	HumanPlayer(GameEngine* game_eng_);
	
	/**
	* @brief prepares the item for playing (focuses the item and backups start position)
	*/
	virtual void Play();
	
	/**
	* @brief moves the player if arrow keys are pressed
	* @param event describes the key pressed
	*/
	void keyPressEvent(QKeyEvent * event);
	
	void keyReleaseEvent(QKeyEvent * event);
	
protected:
	QSet<int> keysPressed;

};

#endif
