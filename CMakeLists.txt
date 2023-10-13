cmake_minimum_required(VERSION 3.26.0)

project(PunkinBot)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory(libs/DPP)

file(GLOB_RECURSE DATA data/*.txt)

add_executable(${PROJECT_NAME} ${DATA} src/main.cpp src/dataType.cpp src/messageCreator.cpp icon.icns)

target_link_libraries(${PROJECT_NAME} dpp)

target_include_directories(${PROJECT_NAME} PRIVATE libs/DPP/include include/)
