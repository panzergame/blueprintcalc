#include <render/point.h>

#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <render/plane.h>

namespace Render
{

Point::Point(Qt3DCore::QEntity *root)
	:Qt3DCore::QEntity(root),
	m_transform(new Qt3DCore::QTransform())
{
	setupGeometry();
}

void Point::setupGeometry()
{
	Qt3DExtras::QSphereMesh *mesh = new Qt3DExtras::QSphereMesh();
	mesh->setRadius(0.01f);

	Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
	material->diffuse() = QColor(1, 0, 0);

	addComponent(m_transform);
	addComponent(mesh);
	addComponent(material);
}

};
