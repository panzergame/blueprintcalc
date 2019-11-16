#pragma once

#include <array>
#include <core/constants.h>
#include <memory>
#include <singleton.h>

namespace Core
{

class Intersection;
class BlueprintView;

class Blueprint : public Singleton<Blueprint>
{
	std::array<std::unique_ptr<BlueprintView>, ImageType::MAX> m_views;
	std::array<std::unique_ptr<Intersection>, IntersectionType::MAX> m_intersections;

public:
	explicit Blueprint();

	BlueprintView *getBlueprintView(ImageType::Type viewType) const;
	Intersection *getIntersection(IntersectionType::Type intersectionType) const;

	void align();
};

} // namespace Core
