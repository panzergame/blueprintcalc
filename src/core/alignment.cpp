#include <QDebug>

#include <core/alignment.h>

namespace Core
{

Alignment::Alignment()
{
	for (unsigned short i = 0; i < IntersectionType::MAX; ++i) {
		IntersectionType::Type intersectionType = IntersectionType::ALL[i];

		qInfo() << intersectionType.axis;

		std::array<QVector3D, 2> directions;
		for (unsigned short j = 0; j < 2; ++j) {
			directions[j] = ImageTransforms[intersectionType.imageViews[j]] * intersectionType.axis;
			qInfo() << intersectionType.imageViews[j] << ImageTransforms[intersectionType.imageViews[j]] << ImageType::NAMES[intersectionType.imageViews[j]] << directions[j];
		}

// 		m_intersections[i] = Intersection();
	}
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
