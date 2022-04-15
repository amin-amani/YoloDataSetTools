cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread")
set(CMAKE_CXX_FLAGS "-fPIC")
set(APP_NAME "YoloClassSplitter")
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui Quick Qml PrintSupport Test SerialPort)
find_package(OpenCV REQUIRED)

add_executable(${APP_NAME} main.cpp ${SOURCES}  ${RESOURCE_FILES}  )
#add_library(${CMAKE_PROJECT_NAME}_lib STATIC)
#add_library(${CMAKE_PROJECT_NAME}_lib  SHARED)
target_link_libraries(
                        ${APP_NAME}
                        Qt5::Core
                        Qt5::Gui
                        Qt5::SerialPort
                        Qt5::Network
                        Qt5::PrintSupport

                      )




set_property(TARGET ${APP_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 14)
