#pragma once

#include <QPointF>
#include <QObject>

namespace Core
{

class Point : public QObject
{
	Q_OBJECT

private:
	QPointF m_position;

public:
	Point(const QPointF& pos);

	void setPosition(const QPointF& pos);
	const QPointF& position() const;

Q_SIGNALS:
	void positionModified(const QPointF& pos);
};

};
