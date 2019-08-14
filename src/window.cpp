#include <QGridLayout>

#include <imageview.h>
#include <3dview.h>
#include <window.h>

Window::Window(View3D *view3D, InfoView *infoView, ImageView *views[ImageViewType::MAX])
{
	QGridLayout *layout = new QGridLayout();

	layout->addWidget(views[ImageViewType::FRONT], 0, 0, 1, 2);
	layout->addWidget(views[ImageViewType::BACK], 0, 3, 1, 2);
	layout->addWidget(views[ImageViewType::SIDE], 0, 2);
	layout->addWidget(views[ImageViewType::TOP], 1, 2);

	layout->addWidget(view3D, 1, 3, 1, 2);

	setLayout(layout);

	show();
}
