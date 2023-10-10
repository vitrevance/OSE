add_subdirectory(lib)

find_package(OpenGL REQUIRED)

option(OSE_DISABLE_LOGGING "Disable logging" OFF)

file(GLOB_RECURSE OSE_SRC_FILES CONFIGURE_DEPENDS
"src/**.cpp"
)

add_library(OSE SHARED ${OSE_SRC_FILES})

target_compile_features(OSE PUBLIC cxx_std_20)
target_compile_definitions(OSE PRIVATE OSE_BUILD GLEW_STATIC ASSIMP_USE_STB_IMAGE_STATIC)

if(OSE_DISABLE_LOGGING)
    target_compile_definitions(OSE PUBLIC OSE_DISABLE_LOGGER)
endif()

set_target_properties(OSE PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(OSE PUBLIC include)

target_link_libraries(OSE PRIVATE glfw libglew_static stb_image assimp)

# clang-tidy
find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
)

if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "--verify-config" "--quiet" "-p=\"${CMAKE_BINARY_DIR}\"")
endif()
set_target_properties(OSE PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")

# Resources

file(GLOB_RECURSE OSE_RESOURCE_FILES CONFIGURE_DEPENDS
"resources/*"
)

message("Found resources:")
foreach(resource  ${OSE_RESOURCE_FILES})
    file(RELATIVE_PATH rel_path ${CMAKE_CURRENT_SOURCE_DIR}/resources ${resource})
    message("* " ${rel_path})
endforeach()

cmrc_add_resource_library(OSE_RESOURCES NAMESPACE OSE WHENCE resources ${OSE_RESOURCE_FILES})

target_link_libraries(OSE PRIVATE OSE_RESOURCES)
