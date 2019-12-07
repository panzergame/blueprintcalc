#include <QGridLayout>
#include <QKeyEvent>
#include <QShortcut>

#include <view/space.h>
#include <view/blueprintview.h>
#include <view/window.h>
#include <view/info.h>

namespace View
{

void Window::shortcutAlignEvent()
{
	Core::Blueprint::singleton->align();
}

void Window::setupUi(Space *space, Info *info, BlueprintView *views[Core::ImageType::MAX])
{
	Ui::MainWindow::setupUi(this);

	row1Layout->addWidget(views[Core::ImageType::FRONT], 1);
	row1Layout->addWidget(views[Core::ImageType::SIDE], 2);
	row1Layout->addWidget(views[Core::ImageType::BACK], 1);

	row2Layout->addWidget(info, 0);
	row2Layout->addWidget(views[Core::ImageType::TOP], 1);
	row2Layout->addWidget(space, 1);

	showMaximized();
}

void Window::setupShortcuts()
{
	m_shortcutAlign.reset(new QShortcut(this));
	m_shortcutAlign->setKey(Qt::CTRL + Qt::Key_A);

	connect(m_shortcutAlign.get(), &QShortcut::activated, this, &Window::shortcutAlignEvent);
}

Window::Window(Space *space, Info *info, BlueprintView *views[Core::ImageType::MAX])
{
	setupUi(space, info, views);
	setupShortcuts();
}

Window::~Window()
{
}

};
