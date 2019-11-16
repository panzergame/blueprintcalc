#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <core/intersection.h>

namespace Render
{

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
