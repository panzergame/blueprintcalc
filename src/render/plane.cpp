#include <render/plane.h>
#include <render/point.h>

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DRender/QTextureImage>

#include <Qt3DCore/QTransform>

constexpr float PLANE_SCALE = 0.001f;

namespace Render
{

Plane::Plane(const QString& imageName, Qt3DCore::QEntity *root)
	:Qt3DCore::QEntity(root),
	m_transform(new Qt3DCore::QTransform())
{
	Qt3DExtras::QPlaneMesh *mesh = new Qt3DExtras::QPlaneMesh();
	mesh->setMirrored(true);

	Qt3DExtras::QTextureMaterial *material = new Qt3DExtras::QTextureMaterial();

	Qt3DRender::QTextureImage *texture = new Qt3DRender::QTextureImage();
	material->texture()->addTextureImage(texture);
	material->setAlphaBlendingEnabled(true);

	const QUrl& url = QUrl::fromLocalFile(imageName);
	texture->setSource(url);

	QImage image(imageName);
	m_size = QPointF(image.width(), image.height());
	mesh->setWidth(m_size.x() * PLANE_SCALE);
	mesh->setHeight(m_size.y() * PLANE_SCALE);

	addComponent(mesh);
	addComponent(material);
	addComponent(m_transform);
}

QVector3D Plane::mapToPlane(const QPointF& pos) const
{
	return QVector3D(pos.x() - m_size.x() / 2.0f, 0.0f, pos.y() - m_size.y() / 2.0f) * PLANE_SCALE;
}

void Plane::transformX(float scaling, float translation)
{
}

void Plane::transformY(float scaling, float translation)
{
}

};
