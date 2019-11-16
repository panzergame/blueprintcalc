#pragma once

#include <QPointF>
#include <core/constants.h>
#include <core/point.h>
#include <singleton.h>

namespace Control
{

class Blueprint : public QObject, public Singleton<Blueprint>
{
	Q_OBJECT

private:
	struct Selection
	{
		Core::Point *point;
		Core::ImageType::Type imageView;
	};

	std::vector<Selection> m_selections;

public:
	explicit Blueprint();
	virtual ~Blueprint();

	// Ajoute un nouveau point à la sequence
	Core::Point *newPoint(Core::ImageType::Type viewType, const QPointF &pos);

Q_SIGNALS:
	void pointAdded(Core::ImageType::Type viewType, Core::Point *point);
};

};
