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

#include <control/blueprint.h>

#include <render/plane.h>
#include <render/point2d.h>
#include <render/point3d.h>
#include <render/scene.h>

namespace Render
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

static std::map<Core::ImageType::Type, std::map<Core::ImageType::Type, QVector3D> > yaxes = imageToImageYAxis(); // TODO move in Core

Scene::Scene(const QStringList &imageNames, Qt3DRender::QCamera *camera)
	:Qt3DCore::QEntity()
{
	setupPlanes(imageNames);
	setupCamera(camera);
	setupSignals();
}

Scene::~Scene()
{
}

void Scene::setupPlanes(const QStringList& imageNames)
{
	Qt3DCore::QEntity *root = new Qt3DCore::QEntity(this);
	Qt3DCore::QTransform *trans = new Qt3DCore::QTransform();
	trans->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f));
	root->addComponent(trans);

	for (Core::ImageType::Type viewType : Core::ImageType::ALL) {
		Core::BlueprintView *view = Core::Blueprint::singleton->getBlueprintView(viewType);
		// Un noeud pour tourner le plan selon son type de vue
		Qt3DCore::QEntity *node = new Qt3DCore::QEntity(root);
		// Le plan avec l'image
		Plane *plane = new Plane(imageNames[viewType], view, node);

		// La transformation pour orienter le plan
		Qt3DCore::QTransform *trans = new Qt3DCore::QTransform();
		trans->setMatrix(view->transform());
		node->addComponent(trans);

		m_planes[viewType] = plane;
	}
}

void Scene::setupCamera(Qt3DRender::QCamera *camera)
{
	// camera
	camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
	camera->setPosition(QVector3D(4.0f, 0.0f, 0.0f));
	camera->setViewCenter(QVector3D(0, 0, 0));

	// For camera controls
	Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(this);
	camController->setLinearSpeed( 5.0f );
	camController->setLookSpeed( 100.0f );
	camController->setCamera(camera);
}

void Scene::setupSignals()
{
	// Écoute de tous les ajouts de pair
	for (Core::IntersectionType::Type intersectionType : Core::IntersectionType::ALL) {
		Core::Intersection *intersection = Core::Blueprint::singleton->getIntersection(intersectionType);
		connect(intersection, &Core::Intersection::pairAdded, this,
				[this, intersectionType](const Core::Intersection::Pair& pair){ this->addPair(intersectionType, pair); });
	}
}

void Scene::addPair(Core::IntersectionType::Type intersectionType, const Core::Intersection::Pair& pair)
{
	std::array<Point3d *, 2> points;

	for (unsigned short i = 0; i < 2; ++i) {
		// Indice de l'autre plan/point
		const unsigned short j = (i + 1) % 2;

		const Core::ImageType::Type selfType = intersectionType.imageViews[i];
		const Core::ImageType::Type otherType = intersectionType.imageViews[j];

		Plane *selfPlane = m_planes[selfType];
		Plane *otherPlane = m_planes[otherType];

		Core::Point *selfPoint = pair.point[i];
		Core::Point *otherPoint = pair.point[j];

		Point3d *point = new Point3d(selfPlane, otherPlane,
				selfPoint, otherPoint, yaxes[selfType][otherType]);

		points[i] = point;
	}

// 	PointGap *gap = new PointGap(points); TODO juste faire la différence
}

};


