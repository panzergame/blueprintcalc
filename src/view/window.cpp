#include <QGridLayout>
#include <QKeyEvent>
#include <QShortcut>

#include <view/space.h>
#include <view/blueprintview.h>
#include <view/window.h>

namespace View
{

void Window::shortcutAlignEvent()
{
	Core::Alignment::singleton->align();
}

void Window::setupUi(Space *space, Info *info, BlueprintView *views[Core::ImageType::MAX])
{
	QGridLayout *layout = new QGridLayout();
// 	QHBoxLayout *layout = new QHBoxLayout();

	layout->addWidget(views[Core::ImageType::FRONT], 0, 0);
	layout->addWidget(views[Core::ImageType::BACK], 0, 3);
	layout->addWidget(views[Core::ImageType::SIDE], 0, 1, 1, 2);
	layout->addWidget(views[Core::ImageType::TOP], 1, 0, 1, 2);
	layout->addWidget(space, 1, 2, 1, 2);

	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 1);
	layout->setColumnStretch(2, 1);
	layout->setColumnStretch(3, 1);

	layout->setRowStretch(0, 1);
	layout->setRowStretch(1, 1);

// 	layout->addWidget(view3D);

	setLayout(layout);

	showMaximized();
}

void Window::setupShortcuts()
{
	m_shortcutAlign = new QShortcut(this);
	m_shortcutAlign->setKey(Qt::CTRL + Qt::Key_A);

	connect(m_shortcutAlign, &QShortcut::activated, this, &Window::shortcutAlignEvent);
}

Window::Window(Space *space, Info *info, BlueprintView *views[Core::ImageType::MAX])
{
	setupUi(space, info, views);
	setupShortcuts();
}

Window::~Window()
{
	delete m_shortcutAlign;
}

};
