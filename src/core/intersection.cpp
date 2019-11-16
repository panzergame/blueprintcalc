#include <QDebug>

#include <core/intersection.h>
#include <core/blueprintview.h>
#include <core/constants.h>

namespace Core
{

Intersection::Intersection(const std::array<QVector3D, 2>& directions,
		const std::array<BlueprintView *, 2> &views)
	:m_directions(directions),
	m_views(views)
{
}

Intersection::~Intersection()
{
}

Intersection::Transform Intersection::alignmentTransform() const
{
	const unsigned int n = m_pairs.size();
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

	qInfo() << s << t;

	Transform transform{t, s};

	return transform;
}

std::array<QVector3D, 2> Intersection::viewWeightedDirection() const
{
	// Multiply view direction by it's freedom factors (weighted)
	std::array<QVector3D, 2> directions = {
		m_directions[0] * m_views[0]->freedomFactors(),
		m_directions[1] * m_views[1]->freedomFactors()
	};

	// Make the sum of each axis equal to 1 (or 0).
	for (unsigned short ai = 0; ai < 3; ++ai) {
		float &a1 = directions[0][ai];
		float &a2 = directions[1][ai];

		const float sum = a1 + a2;
		if (sum != 0.0f) {
			a1 /= sum;
			a2 /= sum;
		}
	}

	return directions;
}

void Intersection::applyPlaneTransform(float weight, const QVector3D& direction, const Transform& transform)
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

	/*if (m_pairs.empty()) {
		return;
	}*/

	const std::array<QVector3D, 2> weights = viewWeightedDirection();

	/* TODO
	 * calculer les facteurs d'influence sum() = 1
	 * appliquer pour chaque vue selon sa direction dans la vue (m_directions).
	 */
}

};
