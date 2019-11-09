#include <QBoxLayout>

#include <Qt3DRender/QCamera>

#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QFirstPersonCameraController>

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <core/blueprint.h>
#include <core/blueprintview.h>

#include <view/space.h>

#include <control/blueprint.h>

#include <render/scene.h>

namespace View
{

Space::Space(const QStringList &imageNames, QWidget *parent)
	:QWidget(parent),
	m_scene(new Render::Scene(imageNames, m_view.camera()))
{
	m_view.setRootEntity(m_scene.get());

	QWidget *content = QWidget::createWindowContainer(&m_view);
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(content);
	setLayout(layout);
}

};


