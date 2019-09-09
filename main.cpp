#include <QApplication>
#include <QDebug>

#include <iostream>

#include <view/space.h>
#include <view/image.h>
#include <view/info.h>
#include <view/window.h>

#include <control/commandline.h>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Control::CommandLine parser(app);
	const QStringList imageNames = parser.GetImageNames();

	View::Image *images[Core::ImageType::MAX];
	for (unsigned short i = 0; i < Core::ImageType::MAX; ++i) {
		const QString &name = imageNames[i];

		images[i] = new View::Image(name, (Core::ImageType::Type)i);
	}

	View::Space *space = new View::Space(imageNames);
	View::Info *info = new View::Info();

	View::Window window(space, info, images);

	app.exec();

	for (unsigned short i = 0; i < Core::ImageType::MAX; ++i) {
		delete images[i];
	}
}
