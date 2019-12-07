#pragma once

#include <QMatrix4x4>
#include <core/constants.h>
#include <memory>
#include <vector>

namespace Core
{

class Point;

class BlueprintView : public QObject
{
	Q_OBJECT

	/// Transformation of plane in 3d.
	const QMatrix4x4 m_basicTransform;
	/// Transformation in plane to align points.
	QMatrix4x4 m_alignmentTransform;
	/// 2d points of this plane.
	std::vector<std::unique_ptr<Point>> m_points;

	std::array<LockAxisType::Type, PlaneAxis::MAX> m_axisFreedom;

public:
	explicit BlueprintView(const QQuaternion &basicRotation);

	const QMatrix4x4 &basicTransform() const;
	QMatrix4x4 transform() const;

	void setAxisFreedom(PlaneAxis::Type axis, LockAxisType::Type freedom);
	LockAxisType::Type axisFreedom(PlaneAxis::Type axis) const;

	/** 3D freedom factors of this view.
	 * 1 for free on this axis otherwise 0
	 */
	QVector3D freedomFactors() const;

	void addPoint(Point *point);

Q_SIGNALS:
	void pointAdded(Point *point);
	void transformUpdated(const QMatrix4x4 &transform);
};

} // namespace Core
