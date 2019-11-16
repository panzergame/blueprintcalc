#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <core/intersection.h>

namespace Render
{

class Line : public Qt3DCore::QEntity
{
private:
	void setupGeometry();

protected:
	Qt3DCore::QTransform *m_transform;

public:
	Line(Qt3DCore::QEntity *root);
};

};
