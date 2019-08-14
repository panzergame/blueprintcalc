#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>

class ImageView : public QGraphicsView
{
protected Q_SLOTS:
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);

public:
	explicit ImageView(const QString &imageFileName, QWidget *parent=nullptr);
	virtual ~ImageView();
};
