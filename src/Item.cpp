
#include "Item.h"
#include "GameView.h"
#include <qt/QtGui/QBrush>
#include <qt/QtCore/QRect>
#include <qt/QtCore/QDebug>
#include <qt/QtGui/QFont>

Item::Item(QPixmap pixmap, const int count_, const int type_, const float intensity_, const float reward_): QGraphicsPixmapItem(pixmap), intensity(intensity_),  type(type_), reward(reward_) {
	
	//set count text
	count_text = new QGraphicsTextItem(QString::number(count_),this);
	count_text->setFont(QFont("Ubuntu",12));
	count_text->setDefaultTextColor(Qt::red);
	count_text->setPos(-10-(64-boundingRect().width())*0.1,-10-(64-boundingRect().height())*0.1);
	if(count_<0) count_text->hide();

}

void Item::setPosIndex(const int sx, const int sy) {
	this->setPos(GameView::rect_margin+sx*64+(64-boundingRect().width())/2, GameView::rect_margin+sy*64+(64-boundingRect().height())/2);
}

void Item::RefreshPosition() {
	setPosIndex(pos.x,pos.y);
}


