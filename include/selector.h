#pragma once

#include <QPointF>

#include <alignment.h>
#include <singleton.h>
#include <enums.h>

class Selector : public QObject, public Singleton<Selector>
{
	Q_OBJECT

private:
	struct Selection
	{
		Alignment::Point *point;
		ImageViewType::Type imageView;
	};

	std::vector<Selection> m_selections;

public:
	Selector();
	virtual ~Selector();

	// Ajoute un nouveau point à la sequence
	Alignment::Point *newPoint(ImageViewType::Type viewType, const QPointF &pos);

Q_SIGNALS:
	void pointAdded(ImageViewType::Type viewType, Alignment::Point *point);
};
