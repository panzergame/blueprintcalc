cmake_minimum_required(VERSION 3.0)

project(blueprintcalc)

find_package(Qt5 COMPONENTS Core Gui Widgets 3DCore 3DExtras 3DRender 3DInput REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
	src/3dview.cpp
	src/commandline.cpp
	src/imageview.cpp
	src/infoview.cpp
	src/pinning.cpp
	src/window.cpp

	main.cpp
	)

add_executable(blueprintcalc ${SRCS})

target_include_directories(blueprintcalc PUBLIC include)
target_link_libraries(blueprintcalc PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets Qt5::3DCore Qt5::3DRender Qt5::3DInput Qt5::3DExtras)
