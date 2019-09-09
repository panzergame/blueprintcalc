#pragma once


#include <vector>
#include <array>

#include <singleton.h>
#include <core/enums.h>
#include <core/intersection.h>

namespace Core
{

class Alignment : public Singleton<Alignment>
{
private:
	std::array<Intersection, IntersectionType::MAX> m_intersections;

public:
	Alignment();

	Intersection& getIntersection(IntersectionType::Type type);
	void align();
};

};
