cmake_minimum_required(VERSION 3.1)

project(nui)

include(core/CMakeLists.txt)
include(widget/CMakeLists.txt)

set(NUI_SOURCE NUI.h NUI.cpp
	${NUI_CORE_SOURCE}
	${NUI_WIDGET_SOURCE}
)

include_directories(${PROJECT_SOURCE_DIR})

add_library(nui ${NUI_SOURCE})