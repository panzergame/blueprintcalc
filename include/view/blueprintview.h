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
	/// Le type de vue du plan. (avant, arrière…).
	Core::ImageType::Type m_viewType;
	/// Un utilitaire pour selectionner et modifier des points.
	Control::BlueprintView m_control;
	/// L'echelle de la vue actuelle.
	float m_scale;

protected Q_SLOTS:
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;

public:
	BlueprintView(const QString &imageFileName, Core::ImageType::Type viewType, QWidget *parent=nullptr);
	virtual ~BlueprintView();
};

};
