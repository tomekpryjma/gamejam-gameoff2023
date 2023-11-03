# CMakeList.txt : CMake project for gamejam-gameoff2023, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.28.5/cmake")
set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.28.5/include")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.28.5/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.28.5/lib/x64/SDL2main.lib;")
else ()
	set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.28.5/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.28.5/lib/x86/SDL2main.lib;")
endif()
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

# Add source to this project's executable.
add_executable (gamejam-gameoff2023 "gamejam-gameoff2023.c"  "core/core.h" "core/core.c"   "game/globals.h" "core/maths/vector2.h" "core/maths/vector2.c" "core/maths/maths.h" "game/player.h" "game/player.c" "game/world.h" "game/world.c" "game/view.h" "game/view.c")
target_link_libraries(gamejam-gameoff2023 ${SDL2_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET gamejam-gameoff2023 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
