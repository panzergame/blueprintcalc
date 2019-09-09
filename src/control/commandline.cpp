#include <QApplication>

#include <control/commandline.h>

namespace Control
{

CommandLine::CommandLine(const QApplication &app)
	:QCommandLineParser()
{
	addPositionalArgument("front", QApplication::translate("main", "Front image"));
	addPositionalArgument("back", QApplication::translate("main", "Back image"));
	addPositionalArgument("top", QApplication::translate("main", "Top image"));
	addPositionalArgument("side", QApplication::translate("main", "Side image"));

	process(app);
}

QStringList CommandLine::GetImageNames() const
{
	return positionalArguments();
}

};
