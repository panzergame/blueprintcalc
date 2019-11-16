#pragma once

#include <QObject>
#include <QVector2D>
#include <QVector3D>
#include <array>
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
	std::array<QVector3D, 2> m_directions;

public:
	explicit Intersection(const std::array<QVector3D, 2> &directions);
	virtual ~Intersection();

	void addPair(const Pair &pair);
	void align();

Q_SIGNALS:
	void transformChangedDirection1(float scaling, float translation, const QVector3D &direction);
	void transformChangedDirection2(float scaling, float translation, const QVector3D &direction);
	void pairAdded(const Pair &pair);
};

};
