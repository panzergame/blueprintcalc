#pragma once

#include <Qt3DCore/QEntity>

class TexturedPlane : public Qt3DCore::QEntity
{
public:
	TexturedPlane(const QString& imageName, Qt3DCore::QEntity *root);
};
