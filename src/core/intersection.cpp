#include <QDebug>

#include <core/intersection.h>

namespace Core
{

Intersection::Intersection()
	:m_scaling(1.0f),
	m_translation(0.0f)
{
}

Intersection::~Intersection()
{
}

void Intersection::addPair(const Pair& pair)
{
	m_pairs.push_back(pair);

	emit pairAdded(pair);
}

void Intersection::align()
{
	qInfo() << "align";
	// magie magie !
}

};
