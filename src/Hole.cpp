#include "Hole.h"

Hole::Hole(const float intensity_, const float reward_) : Item(QPixmap(":/images/hole.png"),-1, Item::HOLE, intensity_, reward_) {
	count_text->setPos(10,10);
}
