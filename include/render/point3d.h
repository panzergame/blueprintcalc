#pragma once

#include <render/point.h>

namespace Render
{

class Plane;

class Point3d : public Point
{
	Q_OBJECT

private:
	Plane *m_plane;
	Plane *m_planeY;

	Core::Point *m_point;
	Core::Point *m_pointY;

	const QVector3D m_yaxis;

	void updatePosition(const QPointF& posPlane, const QPointF& posY);

public:
	Point3d(Plane *plane, Plane *planey, Core::Point *point,
			Core::Point *pointy, const QVector3D& yaxis);

public Q_SLOTS:
	void positionPlaneUpdate(const QPointF& pos);
	void positionYUpdate(const QPointF& pos);
};

};
