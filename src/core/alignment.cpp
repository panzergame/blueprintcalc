#include <QDebug>

#include <core/alignment.h>

namespace Core
{

Alignment::Alignment()
{
}

Intersection &Alignment::getIntersection(IntersectionType::Type type)
{
	return m_intersections[type.index];
}

void Alignment::align()
{
	for (Intersection& intersection : m_intersections) {
		intersection.align();
	}
}

};
