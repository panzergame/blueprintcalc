#pragma once

#include <array>

namespace ImageViewType
{
	enum Type {
		TOP = 0,
		FRONT,
		BACK,
		SIDE,
		MAX
	};
};


namespace IntersectionType
{
	using Type = std::array<ImageViewType::Type, 2>;

	constexpr Type FRONT_SIDE = {ImageViewType::FRONT, ImageViewType::SIDE};
	constexpr Type FRONT_TOP = {ImageViewType::FRONT, ImageViewType::TOP};
	constexpr Type BACK_SIDE = {ImageViewType::BACK, ImageViewType::SIDE};
	constexpr Type BACK_TOP = {ImageViewType::BACK, ImageViewType::TOP};
	constexpr Type SIDE_TOP = {ImageViewType::SIDE, ImageViewType::TOP};

	constexpr unsigned short MAX = 4;
};
