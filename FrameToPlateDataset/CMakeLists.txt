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
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui Quick Qml PrintSupport Test SerialPort)
find_package(OpenCV REQUIRED)
set(PROJECT_NAME FrameToPlateDataset)
set(OPENCV_INC "/usr/local/include/opencv4/")
set(OPENCV_LIBS
    "/usr/local/lib/libopencv_core.so"
    "/usr/local/lib/libopencv_highgui.so"
    "/usr/local/lib/libopencv_imgproc.so"
    "/usr/local/lib/libopencv_imgcodecs.so"
    "/usr/local/lib/libopencv_videoio.so"
    "/usr/local/lib/libopencv_video.so"
    "/usr/local/lib/libopencv_dnn.so"
    libopencv_video.so


    )
include_directories(
    ${OPENCV_INC}

    )

add_executable(${PROJECT_NAME} main.cpp YoloLabel.cpp ${SOURCES}  ${RESOURCE_FILES}  )
#add_library(${CMAKE_PROJECT_NAME}_lib STATIC)
#add_library(${CMAKE_PROJECT_NAME}_lib  SHARED)
target_link_libraries(
                        ${PROJECT_NAME}
                        Qt5::Core
                        Qt5::Gui
                        Qt5::SerialPort
                        Qt5::Network
                        Qt5::PrintSupport
                        ${OPENCV_LIBS}

                      )




set_property(TARGET ${PROJECT_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
