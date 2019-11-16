#include <render/plane.h>
#include <render/point2d.h>

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DRender/QTextureImage>

#include <Qt3DCore/QTransform>

constexpr float PLANE_SCALE = 0.001f;

namespace Render
{

Plane::Plane(const QString& imageName, Core::BlueprintView *view, Qt3DCore::QEntity *root)
	:Qt3DCore::QEntity(root),
	m_blueprintView(view),
	m_transform(new Qt3DCore::QTransform())
{
	// Setup mesh
	Qt3DExtras::QPlaneMesh *mesh = new Qt3DExtras::QPlaneMesh();
	mesh->setMirrored(true);

	// Setup material
	Qt3DExtras::QTextureMaterial *material = new Qt3DExtras::QTextureMaterial();

	// Setup material texture
	Qt3DRender::QTextureImage *texture = new Qt3DRender::QTextureImage();
	material->texture()->addTextureImage(texture);
	material->setAlphaBlendingEnabled(true);

	// Setup texture image
	const QUrl& url = QUrl::fromLocalFile(imageName);
	texture->setSource(url);

	// Track component for rendering
	addComponent(mesh);
	addComponent(material);
	addComponent(m_transform);

	// Scale mesh to image size
	QImage image(imageName);
	m_imageSize = QPointF(image.width(), image.height());
	mesh->setWidth(m_imageSize.x() * PLANE_SCALE);
	mesh->setHeight(m_imageSize.y() * PLANE_SCALE);

	// Setup signals
	connect(m_blueprintView, &Core::BlueprintView::pointAdded, this, &Plane::addPoint);
	connect(m_blueprintView, &Core::BlueprintView::transformUpdated, this, &Plane::updateTransform);
}

QVector3D Plane::mapToPlane(const QPointF& pos) const
{
	return QVector3D(pos.x() - m_imageSize.x() / 2.0f, 0.0f, pos.y() - m_imageSize.y() / 2.0f) * PLANE_SCALE;
}

void Plane::addPoint(Core::Point *point)
{
	Render::Point2d *point2d = new Render::Point2d(this, point);
	m_points.emplace_back(point2d);
}

void Plane::updateTransform(const QMatrix4x4& transform)
{
	m_transform->setMatrix(transform);
}

};
