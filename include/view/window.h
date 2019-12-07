#pragma once

#include <QMainWindow>
#include <core/constants.h>
#include <memory>

#include <ui_window.h>

class QShortcut;

namespace View
{

class Space;
class Info;
class BlueprintView;

class Window : public QMainWindow, private Ui::MainWindow
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
