project ("OSE")
  	kind "SharedLib"
    -- targetdir "../bin/%{cfg.buildcfg}"
    -- objdir "../bin-int"
	language "C++"
    cppdialect "C++20"
	buildoptions { "-Werror=unknown-pragmas" }
    defines { "OSE_BUILD", "GLEW_STATIC" }
    includedirs { "src", "lib" }
    libdirs { "lib/**" }
    files { "**.cpp" }

    filter "configurations:Release"
        defines { "OSE_DISABLE_LOGGER" }
        optimize "On"
    
    filter "configurations:Debug"
        symbols "On"

    filter "system:windows"
        defines { "__windows" }
        links { "glew32s", "opengl32", "glfw3", "gdi32", "assimp", "zlibstatic" }

    filter "system:linux"
        defines { "__linux" }
        links { "pthread", "m", "dl", "glfw", "GL", "GLEW" }
