#include <QBoxLayout>

#include <Qt3DRender/QCamera>

#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QFirstPersonCameraController>

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <3dview.h>
#include <texturedplane.h>

View3D::View3D(const QStringList &imageNames, QWidget *parent)
	:QWidget(parent),
	m_root(new Qt3DCore::QEntity)
{ 
#if 0
	Qt3DCore::QEntity* torus = new Qt3DCore::QEntity(m_root);
	Qt3DCore::QEntity* plane = new Qt3DCore::QEntity(m_root);

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
	torusMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));
// 	Qt3DExtras::QTextureMaterial *planeMaterial = new Qt3DExtras::QTextureMaterial();

	torus->addComponent(mesh);
	torus->addComponent(torusTransform);
	torus->addComponent(torusMaterial);

	plane->addComponent(planeMesh);
	plane->addComponent(torusMaterial);
#endif 
    
	setupCamera();
	setupPlanes(imageNames);

    m_view.setRootEntity(m_root);

	m_view.show();

	QWidget *content = QWidget::createWindowContainer(&m_view);
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(content);
	setLayout(layout);
}

View3D::~View3D()
{
}

void View3D::setupPlanes(const QStringList& imageNames)
{
	static const QQuaternion transforms[ImageViewType::MAX] = {
		QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f),
		QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 90.0f),
		QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), -90.0f),
		QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 0.0f)
	};

	for (unsigned short i = 0; i < imageNames.size(); ++i) {
		TexturedPlane *plane = new TexturedPlane(imageNames[i], m_root);

		Qt3DCore::QTransform *trans = new Qt3DCore::QTransform();
		trans->setRotation(transforms[i]);
		plane->addComponent(trans);

		m_planes[i] = plane;
	}
}

void View3D::setupCamera()
{
	// camera
	Qt3DRender::QCamera *camera = m_view.camera();
	camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
	camera->setPosition(QVector3D(4.0f, 4.0f, 0.0f));
	camera->setViewCenter(QVector3D(0, 0, 0));

	// For camera controls
	Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(m_root);
	camController->setLinearSpeed( 50.0f );
	camController->setLookSpeed( 180.0f );
	camController->setCamera(camera);
}



