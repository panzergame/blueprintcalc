#pragma once

#include <QPointF>

#include <vector>
#include <array>

#include <singleton.h>
#include <enums.h>

class Alignment : public Singleton<Alignment>
{
public:
	struct Point
	{
		QPointF pos;
	};

	struct Pair
	{
		Point *point[2];
	};

	class Intersection : public QObject
	{
	private:
		std::vector<Pair> m_pairs;
		float m_scaling;
		float m_translation;

	public:
		Intersection();

		void addPair(const Pair& pair);
		void align();

	Q_SIGNALS:
		void transformChanged(float scaling, float translation);
	};

private:
	std::array<Intersection, IntersectionType::MAX> m_intersections;

public:
	Alignment();

	Intersection& getIntersection(IntersectionType::Type type);
	void align();
};
