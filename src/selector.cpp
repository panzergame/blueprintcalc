#include <selector.h>

Selector::Selector()
{
}

Selector::~Selector()
{
}

Alignment::Point *Selector::newPoint(ImageViewType::Type viewType, const QPointF& pos)
{
	if (!m_selections.empty()) {
		// Test si les vues séléctionné forment une intersection valide
		IntersectionType::Type intersectionType = IntersectionType::Convert(m_selections[0].imageView, viewType);

		if (intersectionType == IntersectionType::NONE) {
			// N'existe pas
			qInfo() << "doesn't exist";
			return nullptr;
		}
	}

	qInfo() << "new point";

	// Ajout du nouveau point à l'intersection de la tache actuelle
	Alignment::Point *point = new Alignment::Point;
	point->pos = pos;

	emit pointAdded(viewType, point);

	// Enregistrement du point
	Selection selection{point, viewType};
	m_selections.push_back(selection);

	// Arrêt de la tache et enregistrement de l'intersection
	if (m_selections.size() == 2) {
		IntersectionType::Type intersectionType = IntersectionType::Convert(m_selections[0].imageView, m_selections[1].imageView);
		Alignment::Pair pair{m_selections[0].point, m_selections[1].point};
		
		qInfo() << "new pair";
		Alignment::singleton.getIntersection(intersectionType).addPair(pair);

		m_selections.clear();
	}

	return point;
}
