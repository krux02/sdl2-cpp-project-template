project(sdl_template)
cmake_minimum_required(VERSION 2.8.3)

file(GLOB_RECURSE sources src/*.cc src/*.hh)
file(GLOB_RECURSE data data/*)

add_executable(${PROJECT_NAME} ${sources} ${data})

file(COPY ${data} DESTINATION data)

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++1y -Wpedantic -Werror -Wextra -Wall -Wconversion)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)

target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  ${SDL2IMAGE_LIBRARIES}
  ${SDL2MIXER_LIBRARIES}
  ${SDL2TTF_LIBRARIES}
)

