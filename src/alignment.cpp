#include <QDebug>

#include <alignment.h>

Alignment::Intersection::Intersection()
	:m_scaling(1.0f),
	m_translation(0.0f)
{
}

void Alignment::Intersection::addPair(const Alignment::Pair& pair)
{
	m_pairs.push_back(pair);
}

void Alignment::Intersection::align()
{
	qInfo() << "align";
	// magie magie !
}

Alignment::Alignment()
{
}

Alignment::Intersection &Alignment::getIntersection(IntersectionType::Type type)
{
	return m_intersections[type.index];
}

void Alignment::align()
{
	for (Intersection& intersection : m_intersections) {
		intersection.align();
	}
}

