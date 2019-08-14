#include <QMouseEvent>
#include <QWheelEvent>

#include <imageview.h>

void ImageView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier) {
		const QPointF pos = mapToScene(event->pos());
		static const float rad = 1.0f;
		scene()->addEllipse(pos.x() - rad, pos.y() - rad, rad * 2.0f, rad * 2.0f);
	}
	else {
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

ImageView::ImageView(const QString &name, QWidget *parent)
	:QGraphicsView(new QGraphicsScene(), parent)
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
