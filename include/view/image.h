#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>

#include <map>

#include <core/enums.h>
#include <core/alignment.h>

namespace View
{

class Image : public QGraphicsView
{
private:
	Core::ImageType::Type m_viewType;
	std::map<QGraphicsEllipseItem *, Core::Intersection::Point *> m_ellipseToPoint;

protected Q_SLOTS:
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

public:
	explicit Image(const QString &imageFileName, Core::ImageType::Type viewType, QWidget *parent=nullptr);
	virtual ~Image();
};

};
