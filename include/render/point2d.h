#pragma once

#include <render/point.h>

namespace Render
{

class Plane;

class Point2d : public Point
{
	Q_OBJECT

private:
	Plane *m_plane;

	void updatePosition(const QPointF &pos);

public:
	Point2d(Plane *plane, Core::Point *point);

public Q_SLOTS:
	void positionUpdate(const QPointF &pos);
};

};
