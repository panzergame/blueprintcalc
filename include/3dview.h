#pragma once

#include <QWidget>

#include <Qt3DExtras/Qt3DWindow>

class View3D : public QWidget
{
private:
	Qt3DExtras::Qt3DWindow m_view;

public:
	explicit View3D(const QStringList &imageNames, QWidget *parent=nullptr);
	virtual ~View3D();
};
