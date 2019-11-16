#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <core/intersection.h>

namespace Render
{

class Plane : public Qt3DCore::QEntity
{
private:
	Qt3DCore::QTransform *m_transform;
	QPointF m_size;

public:
	Plane(const QString &imageName, Qt3DCore::QEntity *root);

	QVector3D mapToPlane(const QPointF &pos) const;

public Q_SLOTS:
	void transformX(float scaling, float translation);
	void transformY(float scaling, float translation);
};

};
