#include <blueprint/point.h>

#include <QGraphicsItem>

namespace Blueprint
{

Point::Point(QGraphicsEllipseItem *item, Core::Point *point)
	:m_item(item)
{
	connect(this, &Point::updatePosition, point, &Core::Point::positionModified);
}

void Point::updatePosition(const QPointF& pos)
{
	QTransform t; // TODO
	t.translate(pos.x(), pos.y());
	m_item->setTransform(t);
}

};
