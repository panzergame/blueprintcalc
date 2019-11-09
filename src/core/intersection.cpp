#include <QDebug>

#include <core/intersection.h>

namespace Core
{

Intersection::Intersection(const std::array<QVector3D, 2>& directions,
		const std::array<BlueprintView *, 2> &views)
	:m_scaling(1.0f),
	m_translation(0.0f),
	m_directions(directions),
	m_views(views)
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

	const unsigned int n = m_pairs.size();

	if (n == 0) {
		return;
	}

	const float c1 = n;
	float c2 = 0.0f;
	float c3 = 0.0f;
	float c4 = 0.0f;
	float c5 = 0.0f;

	// Calcul des constantes
	for (const Pair& pair : m_pairs) {
		const QPointF posa = pair.point[0]->position();
		const QPointF posb = pair.point[1]->position();

		const float a = QVector3D::dotProduct(m_directions[0], QVector3D(posa.x(), 0.0f, posa.y()));
		const float b = QVector3D::dotProduct(m_directions[1], QVector3D(posb.x(), 0.0f, posb.y()));
		qInfo() << "pair" << a << b << posa << posb;

		// TODO pas * 2
		c2 += b * b;
		c3 += 2.0f * a * b;
		c4 += 2.0f * b;
		c5 += 2.0f * a;
	}

	// Recherche du minimum (le seul point critique)
	const float d = 4 * c1 * c2 - c4 * c4;

	const float s = (2 * c1 * c3 - c4 * c5) / d;
	const float t = -(c3 * c4 - 2 * c2 * c5) / d;

	// Half of the transforms
	const float hs = s / 2.0f;
	const float ht = t / 2.0f;

	// TODO modifier vues

	qInfo() << hs << ht;
}

};
