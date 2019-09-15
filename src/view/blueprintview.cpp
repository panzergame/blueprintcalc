#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QGraphicsItem>

#include <blueprint/point.h>
#include <control/blueprint.h>
#include <view/blueprintview.h>

namespace View
{

void BlueprintView::mousePressEvent(QMouseEvent* event)
{
	const QPointF pos = mapToScene(event->pos());

	if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier) {
		Core::Point *point = Control::Blueprint::singleton.newPoint(m_viewType, pos);

		// Ajout du point pour pouvoir le selectionner plus tard.
		m_control.addPoint(point);
		// Selection automatique du dernier point.
		m_control.selectPoint(point);

		if (point) {
			constexpr float RADIUS = 1.0f;
			QGraphicsEllipseItem *ellipse = scene()->addEllipse(-RADIUS, -RADIUS, RADIUS * 2.0f, RADIUS * 2.0f);

			// Placement du point.
			QTransform t;
			t.translate(pos.x(), pos.y());
			ellipse->setTransform(t);

			// TODO : memoire ?
			// Association vue modèle
			Blueprint::Point *bppoint = new Blueprint::Point(ellipse, point);
		}
	}
	else if (event->button() == Qt::RightButton) {
		// Selection du point le plus près.
		m_control.selectNearestPoint(pos, 100.0f);
	}
	else {
		QGraphicsView::mousePressEvent(event);
	}
}

void BlueprintView::wheelEvent(QWheelEvent* event)
{
	constexpr float SCALE_STEP = 0.2f;

	const float factor = 1.0f + ((event->delta() > 0) ? SCALE_STEP : -SCALE_STEP);

	scale(factor, factor);
	m_scale *= factor;
}

void BlueprintView::keyPressEvent(QKeyEvent *event)
{
	constexpr float MOVE_STEP = 10.0f;

	const float step = MOVE_STEP / m_scale;

	QPointF delta(0.0f, 0.0f);

	if (event->key() == Qt::Key_Left) {
		delta.rx() -= step;
	}
	if (event->key() == Qt::Key_Right) {
		delta.rx() += step;
	}
	if (event->key() == Qt::Key_Up) {
		delta.ry() -= step;
	}
	if (event->key() == Qt::Key_Down) {
		delta.ry() += step;
	}

	m_control.moveSelectedPoint(delta);
}


BlueprintView::BlueprintView(const QString &name, Core::ImageType::Type viewType, QWidget *parent)
	:QGraphicsView(new QGraphicsScene(), parent),
	m_viewType(viewType),
	m_scale(1.0f)
{
	setDragMode(QGraphicsView::ScrollHandDrag);
	scale(0.15f, 0.15f);

	QPixmap pixmap(name);
	scene()->addPixmap(pixmap);
}

BlueprintView::~BlueprintView()
{
	delete scene();
	setScene(nullptr);
}

};
