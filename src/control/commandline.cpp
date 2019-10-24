#include <QApplication>
#include <QDebug>

#include <stdlib.h>

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

	// beuuhh
	if (positionalArguments().size() < 4) {
		qCritical() << "Too few arguments";

		exit(1);
	}
}

QStringList CommandLine::GetImageNames() const
{
	return positionalArguments();
}

};
