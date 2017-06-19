#ifndef HOLE_H
#define HOLE_H
#include <qt/QtGui/QKeyEvent>
#include <qt/QtCore/QSet>
#include <qt/QtCore/QPointF>
#include "Item.h"

class Hole: public Item {
public:
	Hole(const float intensity_, const float reward_);
};

#endif
