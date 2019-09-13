#pragma once

#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>

#include <core/intersection.h>

namespace Render
{

class Plane;

class Point : public Qt3DCore::QEntity
{
private:
	void setupGeometry();

protected:
	Qt3DCore::QTransform *m_transform;

public:
	Point(Qt3DCore::QEntity *root);
};

};