cmake_minimum_required(VERSION 3.0)
project(RenderTest)

file(GLOB render_source "source/*.h" "source/*.cpp")
add_executable(RenderTest ${render_source})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
