#include <QGridLayout>
#include <QKeyEvent>

#include <3dview.h>
#include <imageview.h>
#include <pinning.h>
#include <window.h>

void Window::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_N) {
		m_pinning.newIntersectionTask();
	}
}

Window::Window(View3D *view3D, InfoView *infoView, ImageView *views[ImageViewType::MAX], Pinning &pinning)
	:m_pinning(pinning)
{
// 	QGridLayout *layout = new QGridLayout();
	QHBoxLayout *layout = new QHBoxLayout();

	/*layout->addWidget(views[ImageViewType::FRONT], 0, 0, 1, 2);
	layout->addWidget(views[ImageViewType::BACK], 0, 3, 1, 2);
	layout->addWidget(views[ImageViewType::SIDE], 0, 2);
	layout->addWidget(views[ImageViewType::TOP], 1, 2);*/

// 	layout->addWidget(view3D, 1, 3, 1, 2);

// 	layout->addWidget(view3D);

// 	setLayout(layout);

// 	show();
}
