cmake_minimum_required(VERSION 3.0)
project(spaceward_ho)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL
  GIT_TAG release-2.0.14
)

FetchContent_MakeAvailable(SDL2)

add_executable(spaceward_ho main.cpp)
target_link_libraries(spaceward_ho PRIVATE SDL2::SDL2 SDL2::SDL2main)
