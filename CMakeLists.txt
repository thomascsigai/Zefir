cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GameDev-QuickStart")

find_package(SDL2 REQUIRED)

add_executable (GameDev-QuickStart "src/EntryPoint.cpp" "include/GameConfig.h")
target_include_directories(GameDev-QuickStart PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(GameDev-QuickStart PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Copy SDL2.dll that exists in base project folder
# If it does not exist, find it in your SDL2 folder and copy it.
if (EXISTS ${CMAKE_SOURCE_DIR}/SDL2.dll)
	file(COPY ${CMAKE_SOURCE_DIR}/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
	message(FATAL_ERROR "SDL2.dll not found in project base directory.")
endif()


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameDev-QuickStart PROPERTY CXX_STANDARD 20)
endif()