#include <QGridLayout>
#include <QKeyEvent>

#include <3dview.h>
#include <imageview.h>
#include <alignment.h>
#include <window.h>

void Window::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_A:
		{
			Alignment::singleton.align();
			break;
		}
		default:
		{
			QWidget::keyPressEvent(event);
			break;
		}
	}
}

Window::Window(View3D *view3D, InfoView *infoView, ImageView *views[ImageViewType::MAX])
{
	QGridLayout *layout = new QGridLayout();
// 	QHBoxLayout *layout = new QHBoxLayout();

	layout->addWidget(views[ImageViewType::FRONT], 0, 0);
	layout->addWidget(views[ImageViewType::BACK], 0, 3);
	layout->addWidget(views[ImageViewType::SIDE], 0, 1, 1, 2);
	layout->addWidget(views[ImageViewType::TOP], 1, 0, 1, 2);
	layout->addWidget(view3D, 1, 2, 1, 2);

	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 1);
	layout->setColumnStretch(2, 1);
	layout->setColumnStretch(3, 1);

	layout->setRowStretch(0, 1);
	layout->setRowStretch(1, 1);


// 	layout->addWidget(view3D);

	setLayout(layout);

	show();
}
