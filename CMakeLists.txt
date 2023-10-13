cmake_minimum_required(VERSION 3.14...3.27)

project(
    OSE
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

function(bundle target assets)
    file(GLOB_RECURSE BUNDLE_ASSETS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/${assets}/*"
    )
    set(commands "")
    foreach(resource  ${BUNDLE_ASSETS})
        file(RELATIVE_PATH rel_path ${CMAKE_CURRENT_SOURCE_DIR}/${assets} ${resource})
        set(commands ${commands} COMMAND ${CMAKE_COMMAND} -E copy_if_different ${resource} $<TARGET_FILE_DIR:${target}>/${assets}/${rel_path})
    endforeach()
    add_custom_target(
        ${target}Bundle
        DEPENDS ${target}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:OSE> $<TARGET_FILE_DIR:${target}>/
        ${commands}
        COMMENT "Copy resources to the target directory"
    )
endfunction()

add_subdirectory(OSE)
add_subdirectory(Sandbox)
