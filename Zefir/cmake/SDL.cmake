# SDL2
add_library(SDL2::SDL2 STATIC IMPORTED)
set_target_properties(SDL2::SDL2 PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2-2.32.6/lib/x64/SDL2.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2-2.32.6/include"
)

# SDL2main
add_library(SDL2::SDL2main STATIC IMPORTED)
set_target_properties(SDL2::SDL2main PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2-2.32.6/lib/x64/SDL2main.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2-2.32.6/include"
)

# SDL2_image
add_library(SDL2::SDL2_image STATIC IMPORTED)
set_target_properties(SDL2::SDL2_image PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2_image-2.8.8/lib/x64/SDL2_image.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2_image-2.8.8/include"
)

# SDL2_ttf
add_library(SDL2::SDL2_ttf STATIC IMPORTED)
set_target_properties(SDL2::SDL2_ttf PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2_ttf-2.24.0/lib/x64/SDL2_ttf.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2_ttf-2.24.0/include"
)

# SDL2_mixer
add_library(SDL2::SDL2_mixer STATIC IMPORTED)
set_target_properties(SDL2::SDL2_mixer PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2_mixer-2.8.1/lib/x64/SDL2_mixer.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2_mixer-2.8.1/include"
)
