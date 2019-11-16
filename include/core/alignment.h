#pragma once

#include <array>
#include <core/constants.h>
#include <core/intersection.h>
#include <singleton.h>
#include <vector>

namespace Core
{

class Alignment : public Singleton<Alignment>
{
private:
	std::array<Intersection *, IntersectionType::MAX> m_intersections;

public:
	Alignment();

	Intersection *getIntersection(IntersectionType::Type type);
	void align();
};

};
