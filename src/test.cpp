#include <iostream>
#include <random>
#include <vector>

// #include "lodepng.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMainWindow>
#include <QGridLayout>

#if 1
namespace po = boost::program_options;
namespace pcl {

namespace viz = visualization;

}

enum {
	VIEW_TOP = 0,
	VIEW_FRONT,
	VIEW_BACK,
	VIEW_SIDE,
	VIEW_MAX
} ViewType;

static const char viewNames[VIEW_MAX][10] = {"top", "front", "back", "side"};

class ImageView : public QGraphicsView
{
private:
	QGraphicsScene *m_scene;

// 	Q_OBJECT
protected Q_SLOTS:
	void wheelEvent(QWheelEvent *event)
	{
		if (event->delta() > 0) {
			scale(1.5f, 1.5f);
		}
		else {
			scale(0.5f, 0.5f);
		}
	}

	void mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier) {
			const QPointF pos = mapToScene(event->pos());
			static const float rad = 1.0f;
			m_scene->addEllipse(pos.x() - rad, pos.y() - rad, rad * 2.0f, rad * 2.0f);
		}
		else {
			QGraphicsView::mousePressEvent(event);
		}
	}

	// TODO selectionner un point et le déplacer avec les flèches, Ctrl-Z

public:
	ImageView(QGraphicsScene *scene, QWidget *parent=nullptr)
		:QGraphicsView(scene, parent)
	{
		setDragMode(QGraphicsView::ScrollHandDrag);
	}
};

class Window : public QWidget
{
public:
	explicit Window(ImageView **views)
		:QWidget()
	{
		setAcceptDrops(true);

		/*QGridLayout *layout = new QGridLayout();
		layout->addWidget(views[VIEW_FRONT], 0, 0, 1, 2);
		layout->addWidget(views[VIEW_BACK], 0, 3, 1, 2);
		layout->addWidget(views[VIEW_SIDE], 0, 2);
		layout->addWidget(views[VIEW_TOP], 1, 2);

		setLayout(layout);*/
	}
};

int main(int argc, char **argv)
{
	QApplication a(argc, argv);

	/*QGraphicsScene scenes[VIEW_MAX];
	ImageView *views[VIEW_MAX];
	for (unsigned vi = 0; vi < VIEW_MAX; ++vi) {
		QPixmap pixmap(QString::fromStdString(imageFileNames[vi]));
		QGraphicsScene &scene = scenes[vi];
		scene.addPixmap(pixmap);

		views[vi] = new ImageView(&scene);
	}*/

	Qt3DExtras::Qt3DWindow view;

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
    Qt3DRender::QCamera *camera = view.camera();
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
    
    view.setRootEntity(root);
// 	view.show();

// 	Window window(views);

    QWidget *widget = QWidget::createWindowContainer(&view);

	widget->show();

// 	QHBoxLayout *layout = new QHBoxLayout();
// 	layout->addWidget(widget);
// 	view.show();

// 	window.setLayout(layout);

// 	window.show();

	return a.exec();

// 	return 0;
}
#else

Qt3DCore::QEntity* createTestScene()
{
    Qt3DCore::QEntity* root = new Qt3DCore::QEntity;
    Qt3DCore::QEntity* torus = new Qt3DCore::QEntity(root);

    Qt3DExtras::QTorusMesh* mesh = new Qt3DExtras::QTorusMesh;
    mesh->setRadius(5);
    mesh->setMinorRadius(1);
    mesh->setRings(100);
    mesh->setSlices(20);

    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform;
//    transform->setScale3D(QVector3D(1.5, 1, 0.5));
    transform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1,0,0), 45.f ));

    Qt3DRender::QMaterial* material = new Qt3DExtras::QPhongMaterial(root);

    torus->addComponent(mesh);
    torus->addComponent(transform);
    torus->addComponent(material);

    return root;
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;
    Qt3DCore::QEntity* scene = createTestScene();

    // camera
    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // manipulator
    Qt3DExtras::QOrbitCameraController* manipulator = new Qt3DExtras::QOrbitCameraController(scene);
    manipulator->setLinearSpeed(50.f);
    manipulator->setLookSpeed(180.f);
    manipulator->setCamera(camera);
    
    view.setRootEntity(scene);
    view.show();

    return app.exec();
}

#endif
