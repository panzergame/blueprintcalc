#include <view/info.h>

#include <QBoxLayout>
#include <QPushButton>

namespace View
{

Info::Info()
{
	QHBoxLayout *layout = new QHBoxLayout();

	QPushButton *button = new QPushButton("X");
	layout->addWidget(button);

	setLayout(layout);
}

}
