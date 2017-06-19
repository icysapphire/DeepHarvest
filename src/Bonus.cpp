#include "Bonus.h"
#include <iostream>

Bonus::Bonus(const float intensity_, const float reward_, const int size_) : Item(QPixmap(":/images/strawberry.png").scaled(size_,size_),reward_, Item::BONUS, intensity_, reward_) {

}
