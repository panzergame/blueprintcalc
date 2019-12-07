#pragma once

#include <QTabWidget>

#include <ui_info.h>

namespace View
{

class Info : public QTabWidget, private Ui::Info
{
public:
	explicit Info();
};

};
