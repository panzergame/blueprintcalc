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
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *row1 = new QHBoxLayout();
	QHBoxLayout *row2 = new QHBoxLayout();

	layout->addLayout(row1, 1);
	layout->addLayout(row2, 1);

	row1->addWidget(views[Core::ImageType::FRONT], 1);
	row1->addWidget(views[Core::ImageType::SIDE], 2);
	row1->addWidget(views[Core::ImageType::BACK], 1);

	row2->addWidget(info, 0);
	row2->addWidget(views[Core::ImageType::TOP], 1);
	row2->addWidget(space, 1);

	setLayout(layout);

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
