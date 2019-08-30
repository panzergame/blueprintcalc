#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>

#include <map>

#include <enums.h>
#include <alignment.h>

class ImageView : public QGraphicsView
{
private:
	ImageViewType::Type m_viewType;
	std::map<QGraphicsEllipseItem *, Alignment::Point *> m_ellipseToPoint;

protected Q_SLOTS:
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

public:
	explicit ImageView(const QString &imageFileName, ImageViewType::Type viewType, QWidget *parent=nullptr);
	virtual ~ImageView();
};
