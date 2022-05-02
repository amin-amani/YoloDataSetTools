cmake_minimum_required(VERSION 2.8)
#cmake_minimum_required(VERSION 3.5)

project(YoloDatasetTools LANGUAGES CXX)
set_property(GLOBAL PROPERTY CmakeParentDirectory "${CMAKE_CURRENT_LIST_DIR}")
##pleas add your project settings.these scripts generates config.h with your parameters
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(SRC_DIRECTORY ${PROJECT_SOURCE_DIR})
set(myVAR 12.3)
set(CurrentBranch \"${GIT_BRANCH}\" )
set(CurrentCommit \"${GIT_COMMIT_HASH}\")



include_directories(YoloStatics)
add_subdirectory(YoloStatics)
add_subdirectory(YoloLabelSearch)
add_subdirectory(YoloClassSplitter)
add_subdirectory(FrameToPlateDataset)
add_subdirectory(test)

