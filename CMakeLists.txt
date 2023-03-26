cmake_minimum_required(VERSION 3.26.0)

project(Discord-Message-Bot)

add_subdirectory(libs/DPP)

add_executable(${PROJECT_NAME} src/main.cpp src/dataType.cpp src/messageCreator.cpp)

target_link_libraries(${PROJECT_NAME} dpp)

target_include_directories(${PROJECT_NAME} PRIVATE libs/DPP/include include/)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)