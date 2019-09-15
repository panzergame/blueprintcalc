#include <control/blueprintview.h>

#include <QDebug>

namespace Control
{

BlueprintView::BlueprintView()
	:m_selectedPoint(nullptr)
{
}

void BlueprintView::addPoint(Core::Point *point)
{
	m_points.push_back(point);
}

void BlueprintView::selectPoint(Core::Point* point)
{
	m_selectedPoint = point;
}

void BlueprintView::selectNearestPoint(const QPointF& pos, float tolerance)
{
	Core::Point *nearestPoint = nullptr;
	float minDist2 = tolerance;

	for (Core::Point *point : m_points) {
		const QPointF delta = pos - point->position();
		const float dist2 = delta.x() * delta.x() + delta.y() * delta.y();

		if (dist2 < minDist2) {
			nearestPoint = point;
			minDist2 = dist2;
		}
	}

	qInfo() << nearestPoint;

	m_selectedPoint = nearestPoint;
}

void BlueprintView::moveSelectedPoint(const QPointF& delta)
{
	if (m_selectedPoint) {
		m_selectedPoint->setPosition(m_selectedPoint->position() + delta);
	}
}

};

