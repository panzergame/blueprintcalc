cmake_minimum_required(VERSION 3.14.0)

project(blueprintcalc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -O0")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

find_package(Qt5 COMPONENTS REQUIRED 
	Widgets
	3DCore
	3DRender
	3DExtras
	Gui
)

add_executable(blueprintcalc
    main.cpp

    src/blueprint/point.cpp
    src/control/blueprint.cpp
    src/control/blueprintview.cpp
    src/control/commandline.cpp
    src/core/blueprint.cpp
    src/core/blueprintview.cpp
    src/core/constants.cpp
    src/core/point.cpp
    src/core/intersection.cpp
    src/render/plane.cpp
    src/render/point2d.cpp
    src/render/point3d.cpp
    src/render/point.cpp
    src/render/scene.cpp
    src/view/blueprintview.cpp
    src/view/blueprintviewlock.cpp
    src/view/info.cpp
    src/view/space.cpp
    src/view/window.cpp

    include/blueprint/point.h
    include/control/blueprint.h
    include/control/blueprintview.h
    include/control/commandline.h
    include/core/blueprint.h
    include/core/blueprintview.h
    include/core/constants.h
    include/core/point.h
    include/core/intersection.h
    include/render/plane.h
    include/render/point2d.h
    include/render/point3d.h
    include/render/point.h
    include/render/scene.h
    include/singleton.h
    include/view/blueprintview.h
    include/view/blueprintviewlock.h
    include/view/info.h
    include/view/space.h
    include/view/window.h

    ui/info.ui
)

target_include_directories(blueprintcalc PRIVATE include)

target_link_libraries(blueprintcalc
	Qt5::Widgets
	Qt5::3DCore
	Qt5::3DRender
	Qt5::3DExtras
	Qt5::Gui
)
