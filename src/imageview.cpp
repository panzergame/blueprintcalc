#include <QMouseEvent>
#include <QWheelEvent>

#include <imageview.h>

void ImageView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier) {
		const QPointF pos = mapToScene(event->pos());

		Pinning::Pin *pin = m_pinning.newPin(m_viewType, pos);

		if (pin) {
			static const float rad = 1.0f;
			QGraphicsEllipseItem *ellipse = scene()->addEllipse(pos.x() - rad, pos.y() - rad, rad * 2.0f, rad * 2.0f);

			// Association vue modèle.
			m_ellipseToPin[ellipse] = pin;
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

ImageView::ImageView(const QString &name, ImageViewType::Type viewType, Pinning& pinning, QWidget *parent)
	:QGraphicsView(new QGraphicsScene(), parent),
	m_viewType(viewType),
	m_pinning(pinning)
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
