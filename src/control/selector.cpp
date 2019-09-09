#include <control/selector.h>

namespace Control
{

Selector::Selector()
{
}

Selector::~Selector()
{
}

Core::Intersection::Point *Selector::newPoint(Core::ImageType::Type viewType, const QPointF& pos)
{
	if (!m_selections.empty()) {
		// Test si les vues séléctionné forment une intersection valide
		Core::IntersectionType::Type intersectionType = Core::IntersectionType::Convert(m_selections[0].imageView, viewType);

		if (intersectionType == Core::IntersectionType::NONE) {
			// N'existe pas
			qInfo() << "doesn't exist";
			return nullptr;
		}
	}

	qInfo() << "new point";

	// Ajout du nouveau point à l'intersection de la tache actuelle
	Core::Intersection::Point *point = new Core::Intersection::Point;
	point->pos = pos;

	emit pointAdded(viewType, point);

	// Enregistrement du point
	Selection selection{point, viewType};
	m_selections.push_back(selection);

	// Arrêt de la tache et enregistrement de l'intersection
	if (m_selections.size() == 2) {
		Core::IntersectionType::Type intersectionType = Core::IntersectionType::Convert(m_selections[0].imageView, m_selections[1].imageView);

		// On ordonne les points pour qu'ils respectent l'ordre des images dans le type d'intersection
		const bool reversed = intersectionType.imageViews[0] == m_selections[1].imageView;
		Core::Intersection::Pair pair = reversed ?
			Core::Intersection::Pair{m_selections[1].point, m_selections[0].point} :
			Core::Intersection::Pair{m_selections[0].point, m_selections[1].point};

		qInfo() << "new pair";
		Core::Alignment::singleton.getIntersection(intersectionType).addPair(pair);

		m_selections.clear();
	}

	return point;
}

};
