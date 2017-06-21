#ifndef TEXTITEM_H
#define TEXTITEM_H
#include <qt/QtWidgets/QGraphicsTextItem>
#include <qt/QtCore/QString>
#include <qt/QtCore/QRectF>

class TextItem : public QGraphicsTextItem {
public:

	/**
	 * @brief constructs a new TextItem
	 */
	TextItem(const QString& text, const int x_pos, const int y_pos, const QColor bgcolor_ = BACKGROUND_COLOR);


	virtual QRectF boundingRect(void) const ;

	virtual void paint(
	    QPainter* painter,
	    const QStyleOptionGraphicsItem* option,
	    QWidget* widget);

	virtual QPainterPath shape(void) const;

	/**
	 * @brief gets size of TextItem
	 */
	QSizeF getSize(void) const;

	/**
	 * @brief sets position of TextItem
	 * @param x, y integer coordinates
	 */
	void placeIt(const int x_pos, const int y_pos);
	
	/**
	 * @brief stores a numeric value (custom data) along with the TextItem
	 * @param float value
	 */
	void SetValue(const float v) {numeric_value=v;}
	
	/**
	 * @brief gets the numeric value associated with the TextItem
	 * @return float value
	 */
	float GetValue() {return numeric_value;}

protected:
	QColor bgcolor;
	static const QColor BACKGROUND_COLOR;
	static const qreal MARGIN;
	static const qreal BORDER_WIDTH;
	static const QColor BORDER_COLOR;
	float numeric_value;
};

#endif

