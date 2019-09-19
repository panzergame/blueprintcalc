#pragma once

#include <QObject>
#include <QVector2D>

#include <core/point.h>

namespace Core
{

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
	float m_scaling;
	float m_translation;
	/// Vecteur de l'axe d'intersection dans la base des deux images.
	std::array<QVector2D, 2> m_directions;

public:
	Intersection() = default;
	explicit Intersection(const std::array<QVector2D, 2>& directions);
	virtual ~Intersection();

	void addPair(const Pair& pair);
	void align();

Q_SIGNALS:
	void transformChanged(float scaling, float translation);
	void pairAdded(const Pair& pair);
};

};
