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
		ImageViewType::Type imageViews[2];
		AxisType::Type axis;
	};

	constexpr Type FRONT_SIDE{{ImageViewType::FRONT, ImageViewType::SIDE}, AxisType::Z};
	constexpr Type FRONT_TOP{{ImageViewType::FRONT, ImageViewType::TOP}, AxisType::Y};
	constexpr Type BACK_SIDE{{ImageViewType::BACK, ImageViewType::SIDE}, AxisType::Z};
	constexpr Type BACK_TOP{{ImageViewType::BACK, ImageViewType::TOP}, AxisType::Y};
	constexpr Type SIDE_TOP{{ImageViewType::SIDE, ImageViewType::TOP}, AxisType::X};
	constexpr Type NONE{{ImageViewType::NONE, ImageViewType::NONE}, AxisType::X};

	constexpr unsigned short MAX = 5;

	constexpr std::array<Type, MAX> ALL = {FRONT_SIDE, FRONT_TOP, BACK_SIDE, BACK_TOP, SIDE_TOP};
};
