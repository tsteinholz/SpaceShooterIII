cmake_minimum_required(VERSION 3.2)
project(SpaceShooterIII)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(SOURCE_FILES src/main.cpp inc/scene/scene.h inc/scene/menu.h src/scene/menu.cpp inc/scene/space.h src/scene/space.cpp)
add_executable(SpaceShooterIII ${SOURCE_FILES})

find_package(SFML COMPONENTS Audio Graphics Network System Window)

include_directories(${SFML_INCLUDE_DIR} inc)
target_link_libraries(SpaceShooterIII ${SFML_LIBRARIES})