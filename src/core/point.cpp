#include <core/point.h>

namespace Core
{

Point::Point(const QPointF& pos)
{
	setPosition(pos);
}

void Point::setPosition(const QPointF& pos)
{
	m_position = pos;

	emit positionModified(m_position);
}

const QPointF& Point::position() const
{
	return m_position;
}

};
