#include <view/info.h>

#include <QBoxLayout>
#include <QTabWidget>

#include <core/blueprint.h>
#include <core/constants.h>
#include <view/blueprintviewlock.h>

namespace View
{

Info::Info()
{
	setupUi(this);

	for (Core::ImageType::Type imageType : Core::ImageType::ALL) {
		BlueprintViewLock *lock = new BlueprintViewLock(Core::Blueprint::singleton->getBlueprintView(imageType),
				Core::ImageType::NAMES[imageType]);

		lockTabLayout->addWidget(lock);
	}
}

}
