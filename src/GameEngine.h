#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include <qt/QtWidgets/QApplication>
#include <qt/QtMultimedia/QSoundEffect>
#include "ItemsContainer.h"
#include <opencv2/opencv.hpp>

using namespace std;
class GameView;

class GameEngine {
public:
	GameEngine(const int mode_, const int sizex, const int sizey);
	
	/**
	* @brief inits items container with suitable items at random positions
	*/
	void Init();
	
	inline int GetMode() const {return mode;}
	inline int GetRound() const {return round;}
	inline int GetScore() const {float z=0; if(player!=nullptr) z=player->GetScore(); return z;}
	
	inline int GetWidth() const {return sizeX;}
	inline int GetHeight() const {return sizeY;}
	
	/**
	* @brief calls Play() method on current Player
	*/
	void Play(){
		if(player!=nullptr) player->Play();
	}
	
	/**
	* @brief populates game grid with items from items container
	* @param scene is the game grid, restore is true if grid items backup has to be restored
	*/
	void PopulateGrid(QGraphicsScene* scene, bool restore=false);
	
	/**
	* @brief updates game environment after player's move
	*/
	void Update();
	
	/**
	* @brief exports current game state as a OpenCV matrix
	*/
	void ToMatrix(vector<cv::Mat>& matrix);

	/**
	* @brief returns an empty position on the grid
	*/
	position PickNewPosition();
	
	/**
	* @brief updates current player's score tooltip
	*/
	void SetPlayerTooltipText(const QString str);

protected:
	int round;
	int mode;
	int sizeX, sizeY;
	ItemsContainer items_container;
	Player* player = nullptr;
	QSoundEffect bonus_sound, hole_sound;
};

#endif // GAME_H
