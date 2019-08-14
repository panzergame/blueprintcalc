#include <pinning.h>

Pinning::Pinning()
	:m_task(nullptr)
{
}

void Pinning::newIntersectionTask(IntersectionType::Type intersectionType)
{
	if (m_task) {
		return;
	}

	// Création d'une nouvelle tache
	m_task = new Task;
	m_task->currentView = 0;
	m_task->intersectionType = intersectionType;
}

void Pinning::newPin(ImageViewType::Type viewType, const QPointF &pos)
{
	if (m_task) {
		// Ajout du nouveau point à l'intersection de la tache
		Pin *pin = new Pin;
		pin->pos = pos;

		m_pins.push_back(pin);
		m_task->intersection.pins[m_task->currentView] = pin;

		++m_task->currentView;

		// Arrêt de la tache et enregistrement de l'intersection'
		if (m_task->currentView == 2) {
			m_intersections[m_task->intersectionType].push_back(m_task->intersection);

			delete m_task;
			m_task = nullptr;
		}
	}
}

Pinning::Alignment Pinning::align(IntersectionType::Type intersectionType)
{
	Alignment result;
	return result;
}
