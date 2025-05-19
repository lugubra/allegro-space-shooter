cmake_minimum_required(VERSION 3.28.3)
project(Asteroids C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release)

# Source files
file(GLOB SOURCES "src/*.c")

# Include directories
include_directories(inc)

# Find Allegro 5 packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_main-5 allegro_ttf-5)

include_directories(${ALLEGRO5_INCLUDE_DIRS})
link_directories(${ALLEGRO5_LIBRARY_DIRS})

add_executable(Asteroids ${SOURCES})

target_link_libraries(Asteroids
    ${ALLEGRO5_LIBRARIES}
)

# Copy assets after build
add_custom_command(TARGET Asteroids POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Asteroids>/assets
)
