#pragma once

#include <QCommandLineParser>

#include <array>

#include <enums.h>

class CommandLine : public QCommandLineParser
{
public:
	CommandLine(const QApplication &app);

	QStringList GetImageNames() const;
};
