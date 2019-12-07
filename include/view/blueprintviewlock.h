#pragma once

#include <QWidget>

#include <core/blueprintview.h>

#include <ui_blueprintviewlock.h>

namespace View
{

class BlueprintViewLock : public QWidget, private Ui::BlueprintViewLock
{
private:
	Core::BlueprintView *m_view;

public:
	BlueprintViewLock(Core::BlueprintView *view, const std::string &name);

public Q_SLOTS:
	void axisLocked(Core::PlaneAxis::Type axis, bool checked);
};

};
