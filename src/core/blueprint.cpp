#include <QDebug>

#include <core/blueprint.h>
#include <core/intersection.h>
#include <core/blueprintview.h>

namespace Core
{

Blueprint::Blueprint()
{
	for (ImageType::Type viewType : ImageType::ALL) {
		m_views[viewType].reset(new BlueprintView(ImageTransforms[viewType]));
	}

	for (IntersectionType::Type intersectionType : IntersectionType::ALL) {
		std::array<BlueprintView *, 2> views;
		std::array<QVector3D, 2> directions;
		for (unsigned short j = 0; j < 2; ++j) {
			
			BlueprintView *view = m_views[intersectionType.imageViews[j]].get();
			views[j] = view;
			// Calcule de la direction de l'intersection dans l'espace de la vue
			directions[j] = view->basicTransform() * intersectionType.axis;
		}

		m_intersections[intersectionType.index].reset(new Intersection(directions, views));
	}
}

BlueprintView *Blueprint::getBlueprintView(ImageType::Type viewType) const
{
	return m_views[viewType].get();
}

Intersection *Blueprint::getIntersection(IntersectionType::Type type) const
{
	return m_intersections[type.index].get();
}

void Blueprint::align()
{
	for (const std::unique_ptr<Intersection> &intersection : m_intersections) {
		intersection->align();
	}
}

};
