cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Djipi-App")

if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(Djipi-App
    "${CMAKE_CURRENT_SOURCE_DIR}/src/App.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/utils/Timer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/utils/Texture.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/utils/Texture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/utils/Collision.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/UserEvents.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/Djipi.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/core/Window.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/core/Window.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/core/GameObject.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Player.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Player.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/core/Transform2D.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/core/math/Vector2.h"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/core/math/Vector2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/core/GameObject.cpp"
)

target_include_directories(Djipi-App PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/Djipi/core/math"
)

target_link_libraries(Djipi-App PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)
# Copy SDL2.dll that exists in base project folder
# If it does not exist, find it in your SDL2 folder and copy it.
if (EXISTS ${CMAKE_SOURCE_DIR}/SDL2.dll)
	file(COPY ${CMAKE_SOURCE_DIR}/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(FATAL_ERROR "SDL2.dll not found in project base directory.")
endif()

# Copy SDL2_ttf.dll that exists in base project folder
# If it does not exist, find it in your SDL2_ttf folder and copy it.
if (EXISTS ${CMAKE_SOURCE_DIR}/SDL2_ttf.dll)
	file(COPY ${CMAKE_SOURCE_DIR}/SDL2_ttf.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(FATAL_ERROR "SDL2_ttf.dll not found in project base directory.")
endif()

# Copy SDL2_mixer.dll that exists in base project folder
# If it does not exist, find it in your SDL2_mixer folder and copy it.
if (EXISTS ${CMAKE_SOURCE_DIR}/SDL2_mixer.dll)
	file(COPY ${CMAKE_SOURCE_DIR}/SDL2_mixer.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(FATAL_ERROR "SDL2_mixer.dll not found in project base directory.")
endif()

# Copy Ressources directory to binary dir
if (EXISTS ${CMAKE_SOURCE_DIR}/resources)
	file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(TRACE "No resources directory found.")
endif()


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Djipi-App PROPERTY CXX_STANDARD 20)
endif()