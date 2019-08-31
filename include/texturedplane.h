#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <alignment.h>

class TexturedPlane : public Qt3DCore::QEntity
{
private:
	Qt3DCore::QTransform *m_transform;
	QPointF m_size;

public:
	TexturedPlane(const QString& imageName, Qt3DCore::QEntity *root);

	void addPoint(Alignment::Point *point);

public Q_SLOTS:
	void transformX(float scaling, float translation);
	void transformY(float scaling, float translation);
};
