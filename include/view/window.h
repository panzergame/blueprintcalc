#pragma once

#include <QWidget>

#include <core/constants.h>

namespace View
{

class Space;
class Info;
class BlueprintView;

class Window : public QWidget
{
	Q_OBJECT

protected Q_SLOTS:
	void keyPressEvent(QKeyEvent *event) override;

public:
	Window(Space *space, Info *info, BlueprintView *views[Core::ImageType::MAX]);
	~Window();
};

};
