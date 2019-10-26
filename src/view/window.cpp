#include <QGridLayout>
#include <QKeyEvent>

#include <view/space.h>
#include <view/blueprintview.h>
#include <view/window.h>

namespace View
{

void Window::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_A:
		{
			Core::Alignment::singleton->align();
			break;
		}
		default:
		{
			QWidget::keyPressEvent(event);
			break;
		}
	}
}

Window::Window(Space *space, Info *info, BlueprintView *views[Core::ImageType::MAX])
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

Window::~Window()
{
}

};
