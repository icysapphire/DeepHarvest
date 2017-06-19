#ifndef ITEM_H
#define ITEM_H

#include <qt/QtWidgets/QGraphicsPixmapItem>
#include <qt/QtGui/QPixmap>

/**
* @class position
* @brief Represents a pair of coordinates on the grid.
*/
struct position {
	int x;
	int y;
};

class GameView;

/**
 * @class Item
 * @brief The Item class represents any pickable item the player can run into.
 */

class Item: public QGraphicsPixmapItem {
public:
	Item(QPixmap pixmap,  const int count_=0, const int type_=Item::BOY, const float intensity_=1, const float reward_=0);
	void setPosIndex(const int sx, const int sy);
	void SetPosition(const position pos_){pos=pos_;}
	void RefreshPosition();

	QGraphicsTextItem * count_text;

	float intensity;
	int type;
	float reward;
	position pos;
	
	static const int BOY = 2;
	static const int HOLE =0;
	static const int BONUS = 1;

};

#endif // ITEM_H
