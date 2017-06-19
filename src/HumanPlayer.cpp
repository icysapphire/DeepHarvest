#include "HumanPlayer.h"
#include <qt/QtCore/QSet>

void HumanPlayer::Play() {
	setFlag(QGraphicsItem::ItemIsFocusable,true);
	setFocus();
	start_pos = pos;
}
HumanPlayer::HumanPlayer(GameEngine* game_eng_): Player(game_eng_) {
}
void HumanPlayer::keyPressEvent(QKeyEvent *event) {
	// Just to be sure that a single key is being pressed
	if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Left || event->key() == Qt::Key_Up ||event->key() == Qt::Key_Down) {
		keysPressed.insert(event->key());
	}

	// 0 - up, 1 - down, 2 - left, 3 - right
	if (keysPressed.size() == 1) {
		switch (event->key()) {
		case Qt::Key_Right:
			MoveInDirection(3);
			break;
		case Qt::Key_Left:
			MoveInDirection(2);
			break;
		case Qt::Key_Up:
			MoveInDirection(0);
			break;
		case Qt::Key_Down:
			MoveInDirection(1);
			break;
		}

	}
}

void HumanPlayer::keyReleaseEvent(QKeyEvent *event) {
	keysPressed.remove(event->key());
}
