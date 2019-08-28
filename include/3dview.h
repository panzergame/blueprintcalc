#pragma once

#include <QWidget>

#include <Qt3DExtras/Qt3DWindow>

#include <enums.h>

class TexturedPlane;

class View3D : public QWidget
{
private:
	Qt3DExtras::Qt3DWindow m_view;
	Qt3DCore::QEntity *m_root;
	TexturedPlane *m_planes[ImageViewType::MAX];

	void setupPlanes(const QStringList& imageNames);
	void setupCamera();

public:
	explicit View3D(const QStringList &imageNames, QWidget *parent=nullptr);
	virtual ~View3D();
};
