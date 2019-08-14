#pragma once

#include <QWidget>

#include <enums.h>

class View3D;
class InfoView;
class ImageView;

class Window : public QWidget
{
public:
	explicit Window(View3D *view3D, InfoView *infoView, ImageView *views[ImageViewType::MAX]);
};
