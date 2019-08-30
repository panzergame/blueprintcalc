#include <texturedplane.h>

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DRender/QTextureImage>

#include <Qt3DCore/QTransform>

TexturedPlane::TexturedPlane(const QString& imageName, Qt3DCore::QEntity *root)
	:Qt3DCore::QEntity(root),
	m_transform(new Qt3DCore::QTransform())
{
	Qt3DExtras::QPlaneMesh *mesh = new Qt3DExtras::QPlaneMesh();

	Qt3DExtras::QTextureMaterial *material = new Qt3DExtras::QTextureMaterial();

	Qt3DRender::QTextureImage *texture = new Qt3DRender::QTextureImage();
	material->texture()->addTextureImage(texture);
	material->setAlphaBlendingEnabled(true);

	const QUrl& url = QUrl::fromLocalFile(imageName);
	texture->setSource(url);

	QImage image(imageName);
	mesh->setWidth(image.width() / 1000.0f);
	mesh->setHeight(image.height() / 1000.0f);

	addComponent(mesh);
	addComponent(material);
	addComponent(m_transform);
}

void TexturedPlane::transformX(float scaling, float translation)
{
}

void TexturedPlane::transformY(float scaling, float translation)
{
}

