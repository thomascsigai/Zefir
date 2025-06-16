add_custom_command(TARGET ${ZEFIR_APP} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2-2.32.6/lib/x64/SDL2.dll
        $<TARGET_FILE_DIR:${ZEFIR_APP}>
)

add_custom_command(TARGET ${ZEFIR_APP} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2_image-2.8.8/lib/x64/SDL2_image.dll
        $<TARGET_FILE_DIR:${ZEFIR_APP}>
)

add_custom_command(TARGET ${ZEFIR_APP} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2_mixer-2.8.1/lib/x64/SDL2_mixer.dll
        $<TARGET_FILE_DIR:${ZEFIR_APP}>
)

add_custom_command(TARGET ${ZEFIR_APP} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Zefir/thirdparty/SDL2_ttf-2.24.0/lib/x64/SDL2_ttf.dll
        $<TARGET_FILE_DIR:${ZEFIR_APP}>
)