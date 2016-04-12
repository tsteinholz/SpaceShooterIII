cmake_minimum_required(VERSION 3.2)
project(SpaceShooterIII)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp
						src/gameobjects/graphics/sprite.cpp
						inc/gameobjects/graphics/sprite.h
						src/gameobjects/ui/button.cpp
						inc/gameobjects/ui/button.h)
add_executable(SpaceShooterIII ${SOURCE_FILES})

include_directories (${PROJECT_SOURCE_DIR} inc/ /usr/include/allegro5)
link_directories (/usr/lib)
target_link_libraries (SpaceShooterIII allegro
						allegro_acodec
				       	allegro_audio
				       	allegro_color
				       	allegro_font
				       	allegro_image
				       	allegro_physfs
				       	allegro_primitives
				       	allegro_ttf)
