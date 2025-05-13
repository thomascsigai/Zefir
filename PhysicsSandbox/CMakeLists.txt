#Define application name
set(ZEFIR_APP "PhysicsSandbox")

if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

file(GLOB_RECURSE APP_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_executable(${ZEFIR_APP} ${APP_SRC})

target_include_directories(${ZEFIR_APP} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src

    ${CMAKE_SOURCE_DIR}/Zefir
)

target_link_libraries(${ZEFIR_APP} PRIVATE Zefir)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL_copy.cmake)