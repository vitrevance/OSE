option(OSE_BUILD_SANDBOX "Build the Sandbox for testing purposes" ON)

if(OSE_BUILD_SANDBOX)

    file(GLOB_RECURSE SANDBOX_SRC_FILES CONFIGURE_DEPENDS
    "src/**.cpp"
    )

    add_executable(Sandbox ${SANDBOX_SRC_FILES})

    target_compile_features(Sandbox PUBLIC cxx_std_20)
    set_target_properties(Sandbox PROPERTIES CXX_EXTENSIONS OFF)

    target_include_directories(Sandbox PUBLIC include)

    target_link_libraries(Sandbox PUBLIC OSE)

    bundle(Sandbox assets)

else()
    message("Skipped building the Sandbox")
endif()