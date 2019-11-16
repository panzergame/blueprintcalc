#pragma once

#include <QDebug>
#include <QQuaternion>
#include <QVector3D>
#include <array>

namespace Core
{

/*
 * Z : haut
 * X : arrière
 * Y : gauche
 *
 * plan orienté du côté gauche (Y)
 */

namespace ImageType
{

enum Type
{
	TOP = 0,
	FRONT,
	BACK,
	SIDE,
	MAX,
	NONE
};

constexpr std::array<char[20], MAX> NAMES = {"TOP", "FRONT", "BACK", "SIDE"};

};

static const std::array<QQuaternion, Core::ImageType::MAX> ImageTransforms = {
	QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), -90.0f), // TOP
	QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 90.0f),  // FRONT
	QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), -90.0f), // BACK
	QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 0.0f)	// SIDE
};

namespace AxisType
{

enum Type
{
	PX,
	PY,
	PZ,
	NX,
	NY,
	NZ
};

};

namespace IntersectionType
{

struct Type
{
	short index;
	std::array<ImageType::Type, 2> imageViews;
	QVector3D axis;

	inline bool operator==(const Type &other) const { return index == other.index; }
};

constexpr Type FRONT_SIDE{0, {ImageType::FRONT, ImageType::SIDE}, QVector3D(0.0f, 0.0f, 1.0f)};
constexpr Type FRONT_TOP{1, {ImageType::FRONT, ImageType::TOP}, QVector3D(0.0f, 1.0f, 0.0f)};
constexpr Type BACK_SIDE{2, {ImageType::BACK, ImageType::SIDE}, QVector3D(0.0f, 0.0f, 1.0f)};
constexpr Type BACK_TOP{3, {ImageType::BACK, ImageType::TOP}, QVector3D(0.0f, 1.0f, 0.0f)};
constexpr Type SIDE_TOP{4, {ImageType::SIDE, ImageType::TOP}, QVector3D(1.0f, 0.0f, 0.0f)};
constexpr Type NONE{-1, {ImageType::NONE, ImageType::NONE}, QVector3D()};

constexpr unsigned short MAX = 5;

constexpr std::array<Type, MAX> ALL = {FRONT_SIDE, FRONT_TOP, BACK_SIDE, BACK_TOP, SIDE_TOP};

/// Trouve le type d'intersection pour deux images, renvoie NONE en cas d'échec.
inline Type Convert(ImageType::Type typeA, ImageType::Type typeB)
{
	for (const IntersectionType::Type &intersectionType : ALL) {
		if ((typeA == intersectionType.imageViews[0] && typeB == intersectionType.imageViews[1]) ||
			(typeB == intersectionType.imageViews[0] && typeA == intersectionType.imageViews[1])) {
			return intersectionType;
		}
	}

	return NONE;
}

};

};
