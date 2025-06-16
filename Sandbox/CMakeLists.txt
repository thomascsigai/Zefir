#Define application name
set(ZEFIR_APP "Sandbox")

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

# copy resources folder
set(RESOURCE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(RESOURCE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_custom_command(
    TARGET ${ZEFIR_APP} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${RESOURCE_SOURCE_DIR} ${RESOURCE_BINARY_DIR}
    COMMENT "Copying resource folder to build directory"
)