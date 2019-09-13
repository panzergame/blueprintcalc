#pragma once

#include <core/point.h>

#include <vector>

namespace Control
{

class BlueprintView
{
private:
	std::vector<Core::Point *> m_points;
	Core::Point *m_selectedPoint;

public:
	explicit BlueprintView();

	void addPoint(Core::Point *point);
	void selectNearestPoint(const QPointF& pos, float tolerance);
	void moveSelectedPoint(const QPointF& delta);
};

};
