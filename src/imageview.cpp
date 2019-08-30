#include <QMouseEvent>
#include <QWheelEvent>

#include <imageview.h>
#include <selector.h>

void ImageView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier) {
		const QPointF pos = mapToScene(event->pos());

		Alignment::Point *point = Selector::singleton.newPoint(m_viewType, pos);

		if (point) {
			static const float rad = 1.0f;
			QGraphicsEllipseItem *ellipse = scene()->addEllipse(pos.x() - rad, pos.y() - rad, rad * 2.0f, rad * 2.0f);

			// Association vue modèle.
			m_ellipseToPoint[ellipse] = point;
		}
	} else {
		QGraphicsView::mousePressEvent(event);
	}
}

void ImageView::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0) {
		scale(1.2f, 1.2f);
	}
	else {
		scale(0.8f, 0.8f);
	}
}

ImageView::ImageView(const QString &name, ImageViewType::Type viewType, QWidget *parent)
	:QGraphicsView(new QGraphicsScene(), parent),
	m_viewType(viewType)
{
	setDragMode(QGraphicsView::ScrollHandDrag);
	scale(0.15f, 0.15f);

	QPixmap pixmap(name);
	scene()->addPixmap(pixmap);
}

ImageView::~ImageView()
{
	delete scene();
	setScene(nullptr);
}
