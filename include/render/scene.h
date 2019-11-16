#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <core/constants.h>
#include <core/intersection.h>
#include <memory>

namespace Render
{

class Plane;
class Point3d;

class Scene : public Qt3DCore::QEntity
{
private:
	std::array<Plane *, Core::ImageType::MAX> m_planes;
	std::vector<std::unique_ptr<Point3d>> m_points;

	void setupPlanes(const QStringList &imageNames);
	void setupSignals();
	void setupCamera(Qt3DRender::QCamera *camera);

	void addPair(Core::IntersectionType::Type intersectionType, const Core::Intersection::Pair &pair);

public:
	explicit Scene(const QStringList &imageNames, Qt3DRender::QCamera *camera);
	virtual ~Scene();
};

}; // namespace Render
