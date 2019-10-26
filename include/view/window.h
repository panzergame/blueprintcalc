#pragma once

#include <QWidget>

#include <memory>

#include <core/constants.h>

class QShortcut;

namespace View
{

class Space;
class Info;
class BlueprintView;

class Window : public QWidget
{
	Q_OBJECT
private:
	std::unique_ptr<QShortcut> m_shortcutAlign;

	void setupUi(Space *space, Info *info, BlueprintView *views[Core::ImageType::MAX]);
	void setupShortcuts();

protected Q_SLOTS:
	void shortcutAlignEvent();

public:
	Window(Space *space, Info *info, BlueprintView *views[Core::ImageType::MAX]);
	~Window();
};

};
