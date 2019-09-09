#pragma once

#include <QDebug>

#include <array>

namespace Core
{

namespace ImageType
{
	enum Type {
		TOP = 0,
		FRONT,
		BACK,
		SIDE,
		MAX,
		NONE
	};

	constexpr std::array<char [20], MAX> NAMES = {
		"TOP",
		"FRONT",
		"BACK",
		"SIDE"
	};
};

namespace AxisType
{
	enum Type {
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

		inline bool operator==(const Type& other) const
		{
			return index == other.index;
		}
	};

	constexpr Type FRONT_SIDE{0, {ImageType::FRONT, ImageType::SIDE}};
	constexpr Type FRONT_TOP{1, {ImageType::FRONT, ImageType::TOP}};
	constexpr Type BACK_SIDE{2, {ImageType::BACK, ImageType::SIDE}};
	constexpr Type BACK_TOP{3, {ImageType::BACK, ImageType::TOP}};
	constexpr Type SIDE_TOP{4, {ImageType::SIDE, ImageType::TOP}};
	constexpr Type NONE{-1, {ImageType::NONE, ImageType::NONE}};

	constexpr unsigned short MAX = 5;

	constexpr std::array<Type, MAX> ALL = {FRONT_SIDE, FRONT_TOP, BACK_SIDE, BACK_TOP, SIDE_TOP};

	/// Trouve le type d'intersection pour deux images, renvoie NONE en cas d'échec.
	inline Type Convert(ImageType::Type typeA, ImageType::Type typeB)
	{
		for (const IntersectionType::Type& intersectionType : ALL) {
			if ((typeA == intersectionType.imageViews[0] && typeB == intersectionType.imageViews[1]) ||
				(typeB == intersectionType.imageViews[0] && typeA == intersectionType.imageViews[1]))
			{
				return intersectionType;
			}
		}

		return NONE;
	}
};

};
