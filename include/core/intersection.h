#pragma once

#include <QObject>

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

public:
	Intersection();
	virtual ~Intersection();

	void addPair(const Pair& pair);
	void align();

Q_SIGNALS:
	void transformChanged(float scaling, float translation);
	void pairAdded(const Pair& pair);
};

};
