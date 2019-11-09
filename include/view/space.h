#pragma once

#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>

#include <render/scene.h>

#include <memory>

namespace View
{

class Space : public QWidget
{
	Q_OBJECT

private:
	Qt3DExtras::Qt3DWindow m_view;
	std::unique_ptr<Render::Scene> m_scene;

	void setupCamera();

public:
	Space(const QStringList &imageNames, QWidget *parent = nullptr);
};

};
