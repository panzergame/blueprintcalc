#pragma once

#include <QObject>
#include <core/point.h>

class QGraphicsEllipseItem;

namespace Blueprint
{

/**
 * Un point dans la vue 2d d'un plan.
 * Association de la représentation visuelle du point
 * et du point utilisé par le modèle.
 */
class Point : public QObject
{
	Q_OBJECT

private:
	QGraphicsEllipseItem *m_item;

public:
	Point(QGraphicsEllipseItem *item, Core::Point *point);

protected Q_SLOTS:
	void updatePosition(const QPointF &pos);
};

};
