project ("Sandbox")
  	kind "ConsoleApp"
    -- targetdir "../bin/%{cfg.buildcfg}"
    -- objdir "../bin-int/"
	language "C++"
    cppdialect "C++20"
	buildoptions { "-Werror=unknown-pragmas" }
    includedirs { "src", "lib", "../OSE/src" }
    libdirs { "lib/**", "../bin/%{cfg.buildcfg}" }
    links { "OSE:shared" }
    files { "**.cpp" }
	
    filter "configurations:Release"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"
        defines { "OSE_DISABLE_LOGGER" }

    filter "system:windows"
        defines { "__windows", "WIN64" }
        -- links { "opengl32", "glfw3", "glew32s" }

    filter "system:linux"
        defines { "__linux" }
        -- links { "pthread", "m", "dl", "glfw", "GL", "GLEW" }
    
