#include <texturedplane.h>

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DRender/QTextureImage>

#include <Qt3DCore/QTransform>

constexpr float PLANE_SCALE = 0.001f;

TexturedPlane::TexturedPlane(const QString& imageName, Qt3DCore::QEntity *root)
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

void TexturedPlane::addPoint(Alignment::Point *point)
{
	Qt3DCore::QEntity *node = new Qt3DCore::QEntity(this);

	Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
	material->diffuse() = QColor(0, 0, 0);

	Qt3DExtras::QSphereMesh *mesh = new Qt3DExtras::QSphereMesh();
	mesh->setRadius(0.01f);

	Qt3DCore::QTransform *trans = new Qt3DCore::QTransform();
	const QVector3D pos = QVector3D(point->pos.x() - m_size.x() / 2.0f, 0.0f, point->pos.y() - m_size.y() / 2.0f) * PLANE_SCALE;
	trans->setTranslation(pos);
	qInfo() << point->pos << pos << m_size;

	node->addComponent(trans);
	node->addComponent(mesh);
	node->addComponent(material);
}

void TexturedPlane::transformX(float scaling, float translation)
{
}

void TexturedPlane::transformY(float scaling, float translation)
{
}

