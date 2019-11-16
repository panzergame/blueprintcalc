#pragma once

#include <QObject>
#include <QVector2D>
#include <QVector3D>
#include <array>
#include <core/point.h>

namespace Core
{

class BlueprintView;

class Intersection : public QObject
{
	Q_OBJECT

public:
	struct Pair
	{
		Point *point[2];
	};

private:
	std::vector<Pair> m_pairs;
	/// Vecteur de l'axe d'intersection dans la base des deux images.
	std::array<QVector3D, 2> m_directions;
	/// Les vues en intersection
	std::array<BlueprintView *, 2> m_views;

	// Transform between planes at intersection.
	struct Transform
	{
		float translation;
		float scale;
	};

	Transform alignmentTransform() const;
	std::array<QVector3D, 2> viewWeightedDirection() const;
	void applyPlaneTransform(float weight, const QVector3D& direction, const Transform& transform);

public:
	explicit Intersection(const std::array<QVector3D, 2> &directions,
			const std::array<BlueprintView *, 2> &views);
	virtual ~Intersection();

	void addPair(const Pair &pair);
	void align();

Q_SIGNALS:
	void pairAdded(const Pair &pair);
};

};
