cmake_minimum_required(VERSION 3.12)
project(CAE32_IG C)
find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)

include_directories (include src ${GTK3_INCLUDE_DIRS})
file(GLOB MAIN
	"src/*.c"
	"include/*.h"
)
link_directories (${GTK3_LIBRARY_DIRS})

add_definitions (${GTK3_CFLAGS_OTHER})

add_executable(executable main.c "${MAIN}")

target_link_libraries (executable ${GTK3_LIBRARIES})
