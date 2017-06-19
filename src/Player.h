#ifndef PLAYER_H
#define PLAYER_H


#include "Item.h"

/**
 * @class Player
 * @brief The Player class represents the generic player.
 *
 * It is responsible for moving the character on the grid, receiving score updates, updating tooltips.
 */
class GameEngine;
class Player: public Item {
public:
	Player(GameEngine* game_eng_);

	void AddScore(const float delta);
	inline float GetScore() const { return score; }
	
	/**
	 * @return initial player position
	 */
	inline position GetStartPos() const { return start_pos; }
	
	/**
	 * @return true if the player still has moves to do
	 */
	inline bool CanMove() const { return moves<50; }
	inline int GetMoves() const { return moves;}
	
	/**
	 * @brief moves the player
	 * @param dir is an integer between 0 and 3 (0 - up, 1 - down, 2 - left, 3 - right)
	 * @return true if the move succedeed
	 */
	bool MoveInDirection(const int dir);
	
	virtual void Play() = 0;
	
	
	
protected:
	position start_pos;
	float score;
	int moves;
	GameEngine* game_eng;

};

#endif // PLAYER_H
