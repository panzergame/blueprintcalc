#pragma once

#include <QWidget>

#include <core/enums.h>

namespace View
{

class Space;
class Info;
class Image;

class Window : public QWidget
{
	Q_OBJECT

protected Q_SLOTS:
	void keyPressEvent(QKeyEvent *event) override;

public:
	Window(Space *space, Info *info, Image *images[Core::ImageType::MAX]);
	~Window();
};

};
