#pragma once

#include <QDebug>

#include <array>

namespace ImageViewType
{
	enum Type {
		TOP = 0,
		FRONT,
		BACK,
		SIDE,
		MAX,
		NONE
	};
};

namespace AxisType
{
	enum Type {
		X,
		Y,
		Z
	};
};

namespace IntersectionType
{
	struct Type
	{
		short index;
		std::array<ImageViewType::Type, 2> imageViews;
		AxisType::Type axis;

		inline bool operator==(const Type& other) const
		{
			return index == other.index;
		}
	};

	constexpr Type FRONT_SIDE{0, {ImageViewType::FRONT, ImageViewType::SIDE}, AxisType::Z};
	constexpr Type FRONT_TOP{1, {ImageViewType::FRONT, ImageViewType::TOP}, AxisType::Y};
	constexpr Type BACK_SIDE{2, {ImageViewType::BACK, ImageViewType::SIDE}, AxisType::Z};
	constexpr Type BACK_TOP{3, {ImageViewType::BACK, ImageViewType::TOP}, AxisType::Y};
	constexpr Type SIDE_TOP{4, {ImageViewType::SIDE, ImageViewType::TOP}, AxisType::X};
	constexpr Type NONE{-1, {ImageViewType::NONE, ImageViewType::NONE}, AxisType::X};

	constexpr unsigned short MAX = 5;

	constexpr std::array<Type, MAX> ALL = {FRONT_SIDE, FRONT_TOP, BACK_SIDE, BACK_TOP, SIDE_TOP};

	/// Trouve le type d'intersection pour deux images, renvoie NONE en cas d'échec.
	inline Type Convert(ImageViewType::Type typeA, ImageViewType::Type typeB)
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
