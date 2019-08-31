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
#include <selector.h>
#include <texturedplane.h>

static const QQuaternion transforms[ImageViewType::MAX] = {
	QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), -90.0f), // TOP
	QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 90.0f), // FRONT
	QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), -90.0f), // BACK
	QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 0.0f) // SIDE
};


View3D::View3D(const QStringList &imageNames, QWidget *parent)
	:QWidget(parent),
	m_root(new Qt3DCore::QEntity)
{
	connect(&Selector::singleton, &Selector::pointAdded, this, &View3D::addPoint);
    
	setupCamera();
	setupPlanes(imageNames);

    m_view.setRootEntity(m_root);

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
	Qt3DCore::QEntity *root = new Qt3DCore::QEntity(m_root);
	Qt3DCore::QTransform *trans = new Qt3DCore::QTransform();
	trans->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f));
	root->addComponent(trans);

	for (unsigned short i = 0; i < ImageViewType::MAX; ++i) {
		// Un noeud pour controller l'orientation
		Qt3DCore::QEntity *node = new Qt3DCore::QEntity(root);
		// Le plan avec l'image'
		TexturedPlane *plane = new TexturedPlane(imageNames[i], node);

		// La transformation pour orienter le plan
		Qt3DCore::QTransform *trans = new Qt3DCore::QTransform();
		trans->setRotation(transforms[i]);
		node->addComponent(trans);

		m_planes[i] = plane;
	}
}

void View3D::setupCamera()
{
	// camera
	Qt3DRender::QCamera *camera = m_view.camera();
	camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
	camera->setPosition(QVector3D(4.0f, 0.0f, 0.0f));
	camera->setViewCenter(QVector3D(0, 0, 0));

	// For camera controls
	Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(m_root);
	camController->setLinearSpeed( 5.0f );
	camController->setLookSpeed( 100.0f );
	camController->setCamera(camera);
}

void View3D::addPoint(ImageViewType::Type viewType, Alignment::Point *point)
{
	qInfo() << "point 3d";

	m_planes[viewType]->addPoint(point);
}



