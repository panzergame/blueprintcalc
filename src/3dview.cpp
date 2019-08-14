#include <QBoxLayout>

#include <Qt3DRender/QCamera>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QFirstPersonCameraController>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <3dview.h>

View3D::View3D(const QStringList &imageNames, QWidget *parent)
	:QWidget(parent)
{
    Qt3DCore::QEntity* root = new Qt3DCore::QEntity;
    Qt3DCore::QEntity* torus = new Qt3DCore::QEntity(root);
	Qt3DCore::QEntity* plane = new Qt3DCore::QEntity(root);

    Qt3DExtras::QTorusMesh* mesh = new Qt3DExtras::QTorusMesh;
    mesh->setRadius(5);
    mesh->setMinorRadius(1);
    mesh->setRings(100);
    mesh->setSlices(20);

	Qt3DExtras::QPlaneMesh *planeMesh = new Qt3DExtras::QPlaneMesh();
	planeMesh->setWidth(5);
	planeMesh->setHeight(5);

	Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform();
//    torusTransform->setScale3D(QVector3D(1.5, 1, 0.5));
    torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1,0,0), 45.f ));

	Qt3DExtras::QPhongMaterial *torusMaterial = new Qt3DExtras::QPhongMaterial();
	Qt3DExtras::QTextureMaterial *planeMaterial = new Qt3DExtras::QTextureMaterial();
// 	torusMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));

	torus->addComponent(mesh);
// 	torus->addComponent(torusTransform);
	torus->addComponent(torusMaterial);

	plane->addComponent(planeMesh);
	plane->addComponent(torusMaterial);

    // camera
    Qt3DRender::QCamera *camera = m_view.camera();
//     camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
	camera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
	camera->setFieldOfView(25);
	camera->setNearPlane(0.1f);
	camera->setFarPlane(1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 40, 40));

    // manipulator
    Qt3DExtras::QOrbitCameraController* manipulator = new Qt3DExtras::QOrbitCameraController(root);
    manipulator->setLinearSpeed(50.f);
    manipulator->setLookSpeed(180.f);
    manipulator->setCamera(camera);
    
    m_view.setRootEntity(root);

	QWidget *content = QWidget::createWindowContainer(&m_view);

	QHBoxLayout *layout = new QHBoxLayout();

	layout->addWidget(content);

	setLayout(layout);
}

View3D::~View3D()
{
}
