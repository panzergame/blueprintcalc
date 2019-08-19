#pragma once

#include <QPointF>

#include <vector>
#include <map>

#include <enums.h>

class Pinning
{
public:
	struct Pin
	{
		QPointF pos;
	};

	struct Alignment
	{
		float scaling;
		float translation;
	};

private:
	struct Selection
	{
		Pin *pin = nullptr;
		ImageViewType::Type imageView = ImageViewType::NONE;
	};

	struct Intersection
	{
		std::array<Selection, 2> selections;
	};

	struct Task
	{
		unsigned short currentSelectionIndex = 0;
		Intersection intersection;
	};

	class ValidIntersectionPredicate;

	Task *m_task;
	std::vector<Pin *> m_pins;
	std::map<IntersectionType::Type, std::vector<Intersection> > m_intersections;

public:
	explicit Pinning();

	// Débute une sequence de selection de point sur deux images.
	void newIntersectionTask();
	// Ajoute un nouveau point à la sequence
	Pin *newPin(ImageViewType::Type viewType, const QPointF &pos);

	// Aligne deux images.
	Alignment align(IntersectionType::Type intersectionType);
};
