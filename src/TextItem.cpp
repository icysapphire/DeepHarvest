#include "TextItem.h"
#include <qt/QtWidgets/QApplication>
#include <qt/QtWidgets/QGraphicsItem>
#include <qt/QtWidgets/QGraphicsRectItem>
#include <qt/QtWidgets/QGraphicsScene>
#include <qt/QtWidgets/QGraphicsView>
#include <qt/QtWidgets/QMainWindow>
#include <qt/QtGui/QPainter>
#include <qt/QtCore/QPointF>
#include <qt/QtCore/QSizeF>
#include <qt/QtWidgets/QStyleOptionGraphicsItem>

TextItem::TextItem(const QString& text, const int x_pos, const int y_pos, const QColor bgcolor_): QGraphicsTextItem(0), bgcolor(bgcolor_) {
	setHtml(text);
	placeIt(x_pos, y_pos);
	show();
}


QRectF TextItem::boundingRect(void) const {
	QRectF rect(QPointF(0, 0), getSize());
	qreal d = BORDER_WIDTH / 2;
	rect.adjust(-d, -d, d, d);
	return rect;
}

void TextItem::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget) {
	// Draw surrounding box
	painter->setPen(QPen(BORDER_COLOR, BORDER_WIDTH));
	painter->setBrush(QBrush(bgcolor));
	QRectF rect(QPointF(0, 0), getSize());
	painter->drawRect(rect);

	// Draw text content
	painter->translate(QPointF(MARGIN, MARGIN));
	QGraphicsTextItem::paint(painter, option, widget);
}

QPainterPath TextItem::shape(void) const {
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

QSizeF TextItem::getSize(void) const {
	QRectF rect(QGraphicsTextItem::boundingRect());
	rect.adjust(0, 0, 2*MARGIN, 2*MARGIN);
	return rect.size();
}

void TextItem::placeIt(const int x_pos, const int y_pos) {
	QPointF text_point_in_scene(x_pos, y_pos);
	setPos(text_point_in_scene);
}


const QColor TextItem::BACKGROUND_COLOR(Qt::white);
const qreal TextItem::MARGIN = 5;
const qreal TextItem::BORDER_WIDTH = 1;
const QColor TextItem::BORDER_COLOR(Qt::black);
