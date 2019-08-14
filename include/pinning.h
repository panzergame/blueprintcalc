#pragma once

#include <QPointF>

#include <vector>
#include <map>

#include <enums.h>

class Pinning
{
private:
	struct Pin
	{
		QPointF pos;
	};

	struct Intersection
	{
		union {
			std::array<Pin *, 2> pins;

			struct {
				Pin *pinA;
				Pin *pinB;
			};
		};
	};

	struct Task
	{
		unsigned short currentView;
		IntersectionType::Type intersectionType;
		Intersection intersection;
	};

	Task *m_task;
	std::vector<Pin *> m_pins;
	std::map<IntersectionType::Type, std::vector<Intersection> > m_intersections;

public:
	struct Alignment
	{
		float scaling;
		float translation;
	};

	explicit Pinning();

	// Débute une sequence de selection de point sur deux images.
	void newIntersectionTask(IntersectionType::Type intersectionType);
	// Ajoute un nouveau point à la sequence
	void newPin(ImageViewType::Type viewType, const QPointF &pos);

	// Aligne deux images.
	Alignment align(IntersectionType::Type intersectionType);
};
