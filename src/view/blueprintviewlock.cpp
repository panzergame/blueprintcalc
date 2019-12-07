#include <view/blueprintviewlock.h>

#include <core/blueprint.h>

#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>

namespace View
{

BlueprintViewLock::BlueprintViewLock(Core::BlueprintView *view, const std::string &name)
	:m_view(view)
{
	setupUi(this);
	label->setText(QString::fromStdString(name));

	// Setup freedom state
	const bool lockedX = view->axisFreedom(Core::PlaneAxis::X) == Core::LockAxisType::LOCK;
	const bool lockedZ = view->axisFreedom(Core::PlaneAxis::Z) == Core::LockAxisType::LOCK;

	lockXButton->setChecked(lockedX);
	lockZButton->setChecked(lockedZ);

	connect(lockXButton, &QPushButton::toggled, this, [this](bool checked) { this->axisLocked(Core::PlaneAxis::X, checked); });

	connect(lockZButton, &QPushButton::toggled, this, [this](bool checked) { this->axisLocked(Core::PlaneAxis::Z, checked); });

}

void BlueprintViewLock::axisLocked(Core::PlaneAxis::Type axis, bool checked)
{
	m_view->setAxisFreedom(axis, checked ? Core::LockAxisType::LOCK : Core::LockAxisType::UNLOCK);
}

}
