#include <core/blueprintview.h>
#include <core/point.h>

namespace Core
{

BlueprintView::BlueprintView(const QQuaternion &basicRotation)
	:m_basicTransform(basicRotation.toRotationMatrix()),
	m_axisFreedom({LockAxisType::UNLOCK, LockAxisType::UNLOCK})
{
}

const QMatrix4x4 &BlueprintView::basicTransform() const
{
	return m_basicTransform;
}

QMatrix4x4 BlueprintView::transform() const
{
	return basicTransform() * m_alignmentTransform;
}

void BlueprintView::setAxisFreedom(PlaneAxis::Type axis, LockAxisType::Type freedom)
{
	m_axisFreedom[axis] = freedom;
}

LockAxisType::Type BlueprintView::axisFreedom(PlaneAxis::Type axis) const
{
	return m_axisFreedom[axis];
}

QVector3D BlueprintView::freedomFactors() const
{
	// Factor of every axis locking type.
	static constexpr float lockFactors[LockAxisType::MAX] = {
		0.0f, // LOCK
		1.0f // UNLOCK
	};

	return QVector3D(lockFactors[m_axisFreedom[PlaneAxis::X]], 0.0f, lockFactors[m_axisFreedom[PlaneAxis::Z]]);
}

void BlueprintView::addPoint(Core::Point *point)
{
	m_points.emplace_back(point);

	emit pointAdded(point);
}

}
