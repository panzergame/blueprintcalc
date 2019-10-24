#include <render/point3d.h>
#include <render/plane.h>

namespace Render
{

Point3d::Point3d(Plane *plane, Plane *planey, Core::Point *point,
			Core::Point *pointy, const QVector3D& yaxis)
	:Point(plane),
	m_plane(plane),
	m_planeY(planey),
	m_point(point),
	m_pointY(pointy),
	m_yaxis(yaxis)
{
	updatePosition(m_point->position(), m_pointY->position());

	connect(m_point, &Core::Point::positionModified, this, &Point3d::positionPlaneUpdate);
	connect(m_pointY, &Core::Point::positionModified, this, &Point3d::positionYUpdate);

}

void Point3d::updatePosition(const QPointF& posPlane, const QPointF& posY)
{
	const QVector3D normPosPlane = m_plane->mapToPlane(posPlane);
	const QVector3D normPosY = m_planeY->mapToPlane(posY);

	const float y = QVector3D::dotProduct(m_yaxis, normPosY);

	const QVector3D pos3d(normPosPlane.x(), -y, normPosPlane.z());

	m_transform->setTranslation(pos3d);
}

void Point3d::positionPlaneUpdate(const QPointF& pos)
{
	updatePosition(pos, m_pointY->position());
}

void Point3d::positionYUpdate(const QPointF& pos)
{
	updatePosition(m_point->position(), pos);
}

};
