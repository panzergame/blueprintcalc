#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <core/blueprintview.h>
#include <core/point.h>
#include <memory>
#include <vector>

namespace Render
{

class Point2d;

class Plane : public Qt3DCore::QEntity
{
private:
	QPointF m_imageSize;
	Core::BlueprintView *m_blueprintView;
	Qt3DCore::QTransform *m_transform;

	/// Tracked 2d points in plane
	std::vector<std::unique_ptr<Point2d>> m_points;

public:
	Plane(const QString &imageName, Core::BlueprintView *view, Qt3DCore::QEntity *root);

	QVector3D mapToPlane(const QPointF &pos) const;

public Q_SLOTS:
	void addPoint(Core::Point *point);
	void updateTransform(const QMatrix4x4 &transform);
};

};
