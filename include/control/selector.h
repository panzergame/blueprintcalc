#pragma once

#include <QPointF>

#include <singleton.h>
#include <core/alignment.h>
#include <core/enums.h>

namespace Control
{

class Selector : public QObject, public Singleton<Selector>
{
	Q_OBJECT

private:
	struct Selection
	{
		Core::Intersection::Point *point;
		Core::ImageType::Type imageView;
	};

	std::vector<Selection> m_selections;

public:
	Selector();
	virtual ~Selector();

	// Ajoute un nouveau point à la sequence
	Core::Intersection::Point *newPoint(Core::ImageType::Type viewType, const QPointF &pos);

Q_SIGNALS:
	void pointAdded(Core::ImageType::Type viewType, Core::Intersection::Point *point);
};

};
