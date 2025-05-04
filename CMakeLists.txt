cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Zefir-App")

if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(Zefir-App
    "${CMAKE_CURRENT_SOURCE_DIR}/src/App.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Player.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/renderer/Renderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/resource/ResourceManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/resource/types/Texture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/resource/types/Sound.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/resource/types/Font.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/scene/GameObject.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/window/Window.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/sound/SoundManager.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils/collision/Collision.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils/math/Vector2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils/time/Timer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils/text/TextRendering.cpp"
)

target_include_directories(Zefir-App PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"

    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/thirdparty"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/thirdparty/json-3.12.0"

    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils/collision"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils/debug"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils/math"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils/time"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/utils/text"

    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/resource"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/resource/types"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/resource/types/meta"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/scene"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/window"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/renderer"
    "${CMAKE_CURRENT_SOURCE_DIR}/Zefir/core/sound"
)

target_link_libraries(Zefir-App PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
    SDL2_image::SDL2_image
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

# Copy SDL2_image.dll that exists in base project folder
# If it does not exist, find it in your SDL2_mixer folder and copy it.
if (EXISTS ${CMAKE_SOURCE_DIR}/SDL2_image.dll)
	file(COPY ${CMAKE_SOURCE_DIR}/SDL2_image.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(FATAL_ERROR "SDL2_image.dll not found in project base directory.")
endif()

# Copy Ressources directory to binary dir
if (EXISTS ${CMAKE_SOURCE_DIR}/resources)
	file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(TRACE "No resources directory found.")
endif()


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Zefir-App PROPERTY CXX_STANDARD 20)
endif()