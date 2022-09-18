project ("Sandbox")
  	kind "ConsoleApp"
	language "C++"
    cppdialect "C++20"
	buildoptions { "-Werror=unknown-pragmas" }
    includedirs { "src", "lib", "../OSE/src" }
    libdirs { "lib/**", "../bin/%{cfg.platform}_%{cfg.buildcfg}" }
    links { "OSE:shared" }
    files { "**.cpp" }
	
    filter "configurations:Release"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"
        defines { "OSE_DISABLE_LOGGER" }
        optimize "On"
    
    filter "configurations:Debug"
        symbols "On"

    filter "system:windows"
        defines { "__windows", "WIN64" }

    filter "system:linux"
        defines { "__linux" }
