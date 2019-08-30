#pragma once

#include <QWidget>

#include <Qt3DExtras/Qt3DWindow>

#include <alignment.h>
#include <enums.h>

class TexturedPlane;

class View3D : public QWidget
{
	Q_OBJECT

private:
	Qt3DExtras::Qt3DWindow m_view;
	Qt3DCore::QEntity *m_root;

	void setupPlanes(const QStringList& imageNames);
	void setupCamera();

public:
	View3D(const QStringList &imageNames, QWidget *parent=nullptr);
	virtual ~View3D();

public Q_SLOTS:
	void addPoint(ImageViewType::Type viewType, Alignment::Point *point);
};
