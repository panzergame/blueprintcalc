#pragma once

#include <QWidget>

#include <Qt3DExtras/Qt3DWindow>

#include <core/intersection.h>
#include <core/enums.h>
#include <render/plane.h>

namespace View
{

class Space : public QWidget
{
	Q_OBJECT

private:
	Qt3DExtras::Qt3DWindow m_view;
	Qt3DCore::QEntity *m_root;
	std::array<Render::Plane *, Core::ImageType::MAX> m_planes;

	void setupPlanes(const QStringList& imageNames);
	void setupCamera();

	void addPair(Core::IntersectionType::Type intersectionType, const Core::Intersection::Pair& pair);

public:
	Space(const QStringList &imageNames, QWidget *parent=nullptr);
	virtual ~Space();

public Q_SLOTS:
	void addPoint(Core::ImageType::Type viewType, Core::Point *point);
};

};
