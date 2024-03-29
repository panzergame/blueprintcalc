#include <render/point2d.h>
#include <render/plane.h>

namespace Render
{

Point2d::Point2d(Plane *plane, Core::Point *point)
	:Point(plane),
	m_plane(plane)
{
	updatePosition(point->position());
	connect(point, &Core::Point::positionModified, this, &Point2d::updatePosition);
}

void Point2d::updatePosition(const QPointF& pos)
{
	m_transform->setTranslation(m_plane->mapToPlane(pos));
}

void Point2d::positionUpdate(const QPointF& pos)
{
	updatePosition(pos);
}

};
