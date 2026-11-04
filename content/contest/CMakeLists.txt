cmake_minimum_required(VERSION 4.3)
project(untitled)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-Wall -g -fsanitize=address,undefined
	-fno-sanitize-recover=all -D_GLIBCXX_DEBUG)
add_link_options(-fsanitize=address,undefined)

file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")
foreach(f ${SOURCES})
  get_filename_component(name ${f} NAME_WE)
  add_executable(${name} ${f})
endforeach()
