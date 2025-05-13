add_library(json INTERFACE)
target_include_directories(json INTERFACE
    ${CMAKE_SOURCE_DIR}/Zefir/thirdparty/json-3.12.0
)