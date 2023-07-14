cmake_minimum_required(VERSION 3.26.0)

project(PunkinBot)

add_subdirectory(libs/DPP)

file(GLOB_RECURSE DATA data/*.txt)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE src/main.cpp src/dataType.cpp src/messageCreator.cpp icon.icns ${DATA})

target_link_libraries(${PROJECT_NAME} dpp)

target_include_directories(${PROJECT_NAME} PRIVATE libs/DPP/include include/)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/Info.plist.in"
    RESOURCE "icon.icns"
    MACOSX_BUNDLE_BUNDLE_NAME PunkinBot
    MACOSX_BUNDLE_ICON_FILE icon
    MACOSX_BUNDLE_BUNDLE_VERSION BETA-1.2.1
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_source_files_properties(${DATA} PROPERTIES MACOSX_PACKAGE_LOCATION Resources/data)