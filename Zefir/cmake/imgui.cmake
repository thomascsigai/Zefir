# ImGui sources
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/Zefir/thirdparty/imgui-1.91.9b)

file(GLOB IMGUI_SRC
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer.cpp
)

add_library(ImGui STATIC ${IMGUI_SRC})

target_include_directories(ImGui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(ImGui PUBLIC SDL2::SDL2)