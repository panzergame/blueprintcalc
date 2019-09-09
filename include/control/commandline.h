#pragma once

#include <QCommandLineParser>

class QApplication;

namespace Control
{

class CommandLine : public QCommandLineParser
{
public:
	CommandLine(const QApplication &app);

	QStringList GetImageNames() const;
};

};
