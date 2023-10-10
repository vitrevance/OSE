include(FetchContent)

# GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()
# GLEW
FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG        origin/master
)
FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    FetchContent_Populate(glew)

    add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# assimp
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG        master
)
FetchContent_GetProperties(assimp)
if(NOT assimp_POPULATED)
    FetchContent_Populate(assimp)

    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
    set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "")
    set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE INTERNAL "")
    set(ASSIMP_INSTALL OFF CACHE INTERNAL "")
    set(ASSIMP_INSTALL_PDB OFF CACHE INTERNAL "")
    set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE INTERNAL "")
    set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE INTERNAL "")
    set(USE_STATIC_CRT OFF CACHE INTERNAL "")

    add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
target_compile_definitions(assimp PUBLIC ASSIMP_USE_STB_IMAGE_STATIC)
# std_image
FetchContent_Declare(
    stb_image_src
    GIT_REPOSITORY https://github.com/nothings/stb.git
)
FetchContent_GetProperties(stb_image_src)
if(NOT stb_image_src_POPULATED)
    FetchContent_Populate(stb_image_src)
endif()
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_image_src_SOURCE_DIR})
# cmrc
FetchContent_Declare(
    cmrc
    GIT_REPOSITORY https://github.com/vector-of-bool/cmrc.git
)
FetchContent_GetProperties(cmrc)
if(NOT cmrc_POPULATED)
    FetchContent_Populate(cmrc)

    include(${cmrc_SOURCE_DIR}/CMakeRC.cmake)
endif()
