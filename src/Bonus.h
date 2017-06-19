#ifndef BONUS_H
#define BONUS_H
#include "Item.h"

class Bonus: public Item {
public:
	Bonus(const float intensity_, const float reward_, const int size_);
};

#endif 
