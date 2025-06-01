file(GLOB_RECURSE ZEFIR_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/*.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/*.h

    # Physics not built since Box2D is now used
    #${CMAKE_CURRENT_SOURCE_DIR}/physics/*.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/physics/*.h

    ${CMAKE_CURRENT_SOURCE_DIR}/resource/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resource/*.h

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/*.h

    ${CMAKE_CURRENT_SOURCE_DIR}/sound/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sound/*.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Zefir.h
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
