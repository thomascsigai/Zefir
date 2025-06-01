file(GLOB_RECURSE ZEFIR_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_library(Zefir STATIC ${ZEFIR_SRC})

# Include dependencies
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindDependencies.cmake)

target_include_directories(Zefir PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Zefir PUBLIC
    SDL2::SDL2
    SDL2::SDL2main
    SDL2::SDL2_image
    SDL2::SDL2_ttf
    SDL2::SDL2_mixer
    json
    ImGui
    Box2D
)
