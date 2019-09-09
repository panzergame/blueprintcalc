#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsItem>

#include <view/image.h>
#include <control/selector.h>

namespace View
{

void Image::mousePressEvent(QMouseEvent* event)
{
	const QPointF pos = mapToScene(event->pos());

	if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier) {

		Core::Intersection::Point *point = Control::Selector::singleton.newPoint(m_viewType, pos);

		if (point) {
			static const float rad = 1.0f;
			QGraphicsEllipseItem *ellipse = scene()->addEllipse(-rad, -rad, rad * 2.0f, rad * 2.0f);
			QTransform t;
			t.translate(pos.x(), pos.y());
			ellipse->setTransform(t);

			// Association vue modèle.
			m_ellipseToPoint[ellipse] = point;
		}
	}
	else if (event->button() == Qt::RightButton) {
		QGraphicsItem *item = scene()->itemAt(pos, QTransform());
		QGraphicsEllipseItem *ellipse = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

		qInfo() << ellipse;
	}
	else {
		QGraphicsView::mousePressEvent(event);
	}
}

void Image::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0) {
		scale(1.2f, 1.2f);
	}
	else {
		scale(0.8f, 0.8f);
	}
}

Image::Image(const QString &name, Core::ImageType::Type viewType, QWidget *parent)
	:QGraphicsView(new QGraphicsScene(), parent),
	m_viewType(viewType)
{
	setDragMode(QGraphicsView::ScrollHandDrag);
	scale(0.15f, 0.15f);

	QPixmap pixmap(name);
	scene()->addPixmap(pixmap);
}

Image::~Image()
{
	delete scene();
	setScene(nullptr);
}

};
