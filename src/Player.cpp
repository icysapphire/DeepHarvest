#include "Player.h"
#include "GameEngine.h"
#include "utility.h"
#include <qt/QtGui/QImage>
#include <qt/QtGui/QBrush>
#include <qt/QtCore/QDebug>
#include <qt/QtCore/QString>
#include <qt/QtWidgets/QGraphicsPixmapItem>
#include <qt/QtGui/QPixmap>
#include <qt/QtGui/QKeyEvent>
#include <qt/QtCore/QPointF>


Player::Player(GameEngine* game_eng_): Item(QPixmap(":/images/Boy-64.png")), score(0), moves(0), game_eng(game_eng_){
	pos = game_eng->PickNewPosition();
	setFlag(QGraphicsItem::ItemIsFocusable,true);
	count_text->setDefaultTextColor(Qt::black);
	count_text->setPos(0,32);
}
bool Player::MoveInDirection(const int dir) {
	// 0 - up, 1 - down, 2 - left, 3 - right
	bool moved=false;
	if (dir == 0 && pos.y >= 1)
		{pos.y -= 1; moved = true;}
	else if (dir == 1 && pos.y <= game_eng->GetHeight()-2)
		{pos.y += 1; moved = true;}
	else if (dir == 2 && pos.x >= 1)
		{pos.x -= 1; moved = true;}
	else if (dir == 3 && pos.x <= game_eng->GetWidth()-2)
		{pos.x += 1; moved = true;}

	RefreshPosition();
	moves++;
	game_eng->Update();
	return moved;
}

void Player::AddScore(const float delta) {
	score +=delta;
	count_text -> setHtml(utility::qstring_placeholder("<div style='background-color:white;border:1px solid #ccc'>%1%</div>", (int) score));
}





