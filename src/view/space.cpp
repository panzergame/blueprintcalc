#include <QBoxLayout>

#include <Qt3DRender/QCamera>

#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QFirstPersonCameraController>

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <core/alignment.h>
#include <view/space.h>
#include <control/blueprint.h>
#include <render/plane.h>
#include <render/point2d.h>

namespace View
{

/** Calcule les axes Y de la base d'une image dans la base d'une autre
 * Seulement les axes entre des images en intersection
 */
static std::map<Core::ImageType::Type, std::map<Core::ImageType::Type, QVector3D> > imageToImageYAxis()
{
	std::map<Core::ImageType::Type, std::map<Core::ImageType::Type, QVector3D> > map;

	for (Core::IntersectionType::Type intersectionType : Core::IntersectionType::ALL) {
		const Core::ImageType::Type imageA = intersectionType.imageViews[0];
		const Core::ImageType::Type imageB = intersectionType.imageViews[1];

		static const QVector3D axisY(0.0f, 1.0f, 0.0f);
		// Transformation entre les deux images
		const QQuaternion trans = Core::ImageTransforms[imageB] *
			Core::ImageTransforms[imageA].inverted();

		map[imageA][imageB] = trans * axisY;
		map[imageB][imageA] = trans.inverted() * axisY;

		qInfo() << Core::ImageType::NAMES[imageA] << Core::ImageType::NAMES[imageB] << map[imageA][imageB];
		qInfo() << Core::ImageType::NAMES[imageB] << Core::ImageType::NAMES[imageA] << map[imageB][imageA];
	}

	return map;
}

static std::map<Core::ImageType::Type, std::map<Core::ImageType::Type, QVector3D> > yaxes = imageToImageYAxis();

Space::Space(const QStringList &imageNames, QWidget *parent)
	:QWidget(parent),
	m_root(new Qt3DCore::QEntity)
{
	// Écoute des ajouts de points
	connect(Control::Blueprint::singleton, &Control::Blueprint::pointAdded, this, &Space::addPoint);

	// Écoute de tous les ajouts de pair
	for (Core::IntersectionType::Type intersectionType : Core::IntersectionType::ALL) {
		Core::Intersection& intersection = Core::Alignment::singleton->getIntersection(intersectionType);
		connect(&intersection, &Core::Intersection::pairAdded, this,
				[this, intersectionType](const Core::Intersection::Pair& pair){ this->addPair(intersectionType, pair); });
	}
    
	setupCamera();
	setupPlanes(imageNames);

    m_view.setRootEntity(m_root);

	QWidget *content = QWidget::createWindowContainer(&m_view);
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(content);
	setLayout(layout);
}

Space::~Space()
{
}

void Space::setupPlanes(const QStringList& imageNames)
{
	Qt3DCore::QEntity *root = new Qt3DCore::QEntity(m_root);
	Qt3DCore::QTransform *trans = new Qt3DCore::QTransform();
	trans->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f));
	root->addComponent(trans);

	for (unsigned short i = 0; i < Core::ImageType::MAX; ++i) {
		// Un noeud pour controller l'orientation
		Qt3DCore::QEntity *node = new Qt3DCore::QEntity(root);
		// Le plan avec l'image'
		Render::Plane *plane = new Render::Plane(imageNames[i], node);

		// La transformation pour orienter le plan
		Qt3DCore::QTransform *trans = new Qt3DCore::QTransform();
		trans->setRotation(Core::ImageTransforms[i]);
		node->addComponent(trans);

		m_planes[i] = plane;
	}
}

void Space::setupCamera()
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

void Space::addPoint(Core::ImageType::Type viewType, Core::Point *point)
{
	qInfo() << "point 3d";

	Render::Point2d *p = new Render::Point2d(m_planes[viewType], point);
}

void Space::addPair(Core::IntersectionType::Type intersectionType, const Core::Intersection::Pair& pair)
{
	for (unsigned short i = 0; i < 2; ++i) {
		const Core::ImageType::Type selfType = intersectionType.imageViews[i];
		const Core::ImageType::Type otherType = intersectionType.imageViews[(i + 1) % 2];

		Render::Plane *selfPlane = m_planes[selfType];
		Render::Plane *otherPlane = m_planes[otherType];

		const QVector3D selfPoint = selfPlane->mapToPlane(pair.point[i]->position());
		const QVector3D otherPoint = otherPlane->mapToPlane(pair.point[(i + 1) % 2]->position());

		const float y = QVector3D::dotProduct(yaxes[selfType][otherType], otherPoint);

		const QVector3D point(selfPoint.x(), -y, selfPoint.z());
		qInfo() << point;

// 		selfPlane->addPairPoint(point);
	}
}

};


