cmake_minimum_required(VERSION 3.2)
project(SpaceShooterIII)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(SOURCE_FILES src/main.cpp
	src/gameobjects/graphics/sprite.cpp
	src/gameobjects/ui/button.cpp
	src/gameobjects/physics/projectile.cpp
)
add_executable(SpaceShooterIII ${SOURCE_FILES})

IF (WIN32)
  include_directories (${PROJECT_SOURCE_DIR} inc/ bin/ /usr/include/allegro5)
ELSE()
  include_directories (${PROJECT_SOURCE_DIR} inc/ /usr/include/allegro5)
ENDIF()
link_directories (/usr/lib)
target_link_libraries (SpaceShooterIII
	allegro
	allegro_acodec
	allegro_audio
	allegro_color
	allegro_font
	allegro_image
	allegro_physfs
	allegro_primitives
	allegro_ttf)
