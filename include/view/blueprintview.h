#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>

#include <core/enums.h>
#include <core/alignment.h>
#include <control/blueprintview.h>

namespace View
{

class BlueprintView : public QGraphicsView
{
private:
	Core::ImageType::Type m_viewType;
	Control::BlueprintView m_control;

protected Q_SLOTS:
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

public:
	BlueprintView(const QString &imageFileName, Core::ImageType::Type viewType, QWidget *parent=nullptr);
	virtual ~BlueprintView();
};

};
