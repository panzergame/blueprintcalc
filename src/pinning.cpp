#include <QDebug>

#include <pinning.h>

Pinning::Pinning()
	:m_task(nullptr)
{
}

void Pinning::newIntersectionTask()
{
	if (m_task) {
		return;
	}

	qInfo() << "new task";

	// Création d'une nouvelle tache
	m_task = new Task;
}

class Pinning::ValidIntersectionPredicate
{
private:
	const Intersection& m_intersection;

public:
	ValidIntersectionPredicate(const Intersection& intersection)
		:m_intersection(intersection)
	{
	}

	bool operator()(const IntersectionType::Type intersectionType)
	{
		return (intersectionType.imageViews[0] == m_intersection.selections[0].imageView &&
		intersectionType.imageViews[1] == m_intersection.selections[1].imageView) ||
		(intersectionType.imageViews[0] == m_intersection.selections[1].imageView &&
		intersectionType.imageViews[1] == m_intersection.selections[0].imageView);
	}
};

Pinning::Pin *Pinning::newPin(ImageViewType::Type viewType, const QPointF &pos)
{
	if (!m_task) {
		return nullptr;
	}

	Intersection &intersection = m_task->intersection;
	Selection& selection = intersection.selections[m_task->currentSelectionIndex];

	// Ajout du type de la vue.
	selection.imageView = viewType;

	if (m_task->currentSelectionIndex > 0) {
		// Test si les vues séléctionné forment une intersection valide
		const auto &it = std::find_if(IntersectionType::ALL.begin(), IntersectionType::ALL.end(), ValidIntersectionPredicate(intersection));

		if (it == IntersectionType::ALL.end()) {
			// N'existe pas
			qInfo() << "doesn't exist";
			return nullptr;
		}
	}

	qInfo() << "new pin";

	// Ajout du nouveau point à l'intersection de la tache actuel
	Pin *pin = new Pin;
	pin->pos = pos;

	// Enregistrement du point
	m_pins.push_back(pin);
	selection.pin = pin;

	++m_task->currentSelectionIndex;

	// Arrêt de la tache et enregistrement de l'intersection'
	if (m_task->currentSelectionIndex == 2) {
// 		m_intersections[intersection.intersectionType].push_back(m_task->intersection); TODO

		delete m_task;
		m_task = nullptr;
	}

	return pin;
}

Pinning::Alignment Pinning::align(IntersectionType::Type )
{
	qInfo() << "align";

	Alignment result;
	/*const std::vector<Intersection> & intersections = m_intersections[intersectionType];
	const unsigned short n = intersections.size();

	float c1 = (float)n;
	float c2 = 0.0f;
	float c3 = 0.0f;
	float c4 = 0.0f;
	float c5 = 0.0f;

	// Calcules des constantes
	for (Intersection intersection : intersections) {
		const float a;
		const float b;

		c2 += b * b;
		c3 += 2.0f * a * b;
		c4 += 2.0f * b;
		c5 += 2.0f * a;
	}*/

	return result;
}
