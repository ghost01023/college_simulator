cmake_minimum_required(VERSION 3.27)
project(CollegeSimulator C)

set(CMAKE_C_STANDARD 23)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

#add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(CollegeSimulator main.c
        gtk.c
)
target_link_libraries(${PROJECT_NAME} ${GTK_LIBRARIES})

