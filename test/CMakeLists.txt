cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "-fPIC")
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui Quick Qml PrintSupport Test SerialPort)
find_package( OpenCV REQUIRED )

set(PTHREAD_LIB "/usr/lib/x86_64-linux-gnu/libpthread.so")
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
#set(PROJECT_LIB "${CMAKE_BINARY_DIR}/src/libSorterNew_lib.so")
#file(GLOB_RECURSE HEADERS LIST_DIRECTORIES true ${SRC_DIRECTORY}/FrameToPlateDataset/*.h   )



include_directories(
${OPENCV_INC}
${Qt5Core_INCLUDE_DIRS}
${Qt5Test_INCLUDE_DIRS}
${Qt5Gui_INCLUDE_DIRS}
${Qt5Widgets_INCLUDE_DIRS}
${Qt5Network_INCLUDE_DIRS}
${SRC_DIRECTORY}/FrameToPlateDataset
)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SRC_DIRECTORY}/FrameToPlateDataset/*.h  ${SRC_DIRECTORY}/FrameToPlateDataset/*.cpp  )
list(REMOVE_ITEM SOURCES ${SRC_DIRECTORY}/FrameToPlateDataset/main.cpp)
set(SOURCES
    ${SOURCES}
    ${TRT_SRC}
    ${SRC_DIRECTORY}
    )

message("=======================>" ${HEADERS})

set(
    USED_LIB
    ${PTHREAD_LIB}
    ${OPENCV_LIBS}
    Qt5::Test
    Qt5::Gui
    Qt5::SerialPort
    Qt5::Network


    )


enable_testing()
#add_executable(Template_test tst_Template.cpp)
#target_link_libraries(Template_test ${USED_LIB} )
#add_test(NAME Template_test COMMAND Template_test)
#//tst_FrameToPlate
add_executable(FrameToPlate_test tst_FrameToPlate.cpp  ${SOURCES})
target_link_libraries(FrameToPlate_test ${USED_LIB} )
add_test(NAME FrameToPlate_test COMMAND FrameToPlate_test)
