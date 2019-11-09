#include <QApplication>
#include <QDebug>

#include <iostream>

#include <view/space.h>
#include <view/blueprintview.h>
#include <view/info.h>
#include <view/window.h>

#include <core/blueprint.h>

#include <control/blueprint.h>
#include <control/commandline.h>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Control::CommandLine parser(app);
	const QStringList imageNames = parser.GetImageNames();

	Core::Blueprint::initSingleton();
	Control::Blueprint::initSingleton();

	View::BlueprintView *views[Core::ImageType::MAX];
	for (unsigned short i = 0; i < Core::ImageType::MAX; ++i) {
		const QString &name = imageNames[i];

		views[i] = new View::BlueprintView(name, (Core::ImageType::Type)i);
	}

	View::Space *space = new View::Space(imageNames);
	View::Info *info = new View::Info();

	View::Window window(space, info, views);

	app.exec();

	for (unsigned short i = 0; i < Core::ImageType::MAX; ++i) {
		delete views[i];
	}
}
