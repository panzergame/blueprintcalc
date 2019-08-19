#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>

#include <map>

#include <enums.h>
#include <pinning.h>

class ImageView : public QGraphicsView
{
private:
	ImageViewType::Type m_viewType;
	Pinning &m_pinning;
	std::map<QGraphicsEllipseItem *, Pinning::Pin *> m_ellipseToPin;

protected Q_SLOTS:
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

public:
	explicit ImageView(const QString &imageFileName, ImageViewType::Type viewType, Pinning &pinning, QWidget *parent=nullptr);
	virtual ~ImageView();
};
