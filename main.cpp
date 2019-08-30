#include <QApplication>
#include <QDebug>

#include <iostream>

#include <3dview.h>
#include <commandline.h>
#include <imageview.h>
#include <infoview.h>
#include <window.h>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	CommandLine parser(app);
	const QStringList imageNames = parser.GetImageNames();

	ImageView *imageViews[ImageViewType::MAX];
	for (unsigned short i = 0; i < ImageViewType::MAX; ++i) {
		const QString &name = imageNames[i];

		imageViews[i] = new ImageView(name, (ImageViewType::Type)i);
	}

	View3D *view3D = new View3D(imageNames);
	InfoView *infoView = new InfoView();

	Window window(view3D, infoView, imageViews);

	app.exec();

	for (unsigned short i = 0; i < ImageViewType::MAX; ++i) {
		delete imageViews[i];
	}
}
