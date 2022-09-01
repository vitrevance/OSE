
function string.starts(String,Start)
    return string.sub(String,1,string.len(Start))==Start
end

workspaceName = path.getbasename(os.getcwd())

workspace (workspaceName)
    configurations { "Debug", "Release"}
    platforms { "x64" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:x64" }
        architecture "x86_64"
    filter {}
	
    targetdir "bin/%{cfg.buildcfg}/"

include ("OSE")

folders = os.matchdirs("*")
for _, folderName in ipairs(folders) do
    if (string.starts(folderName, "OSE") == false and string.starts(folderName, "_") == false and string.starts(folderName, ".") == false) then
        if (os.isfile(folderName .. "/premake5.lua")) then
            print(folderName)
            include (folderName)
        end
    end
end

newaction {
    trigger     = "clean",
    description = "clean binaries and objects",
    execute     = function ()
        print("clean the build...")
        os.rmdir("./bin")
        os.rmdir("./obj")
        print("done.")
    end
}

newaction {
    trigger     = "rmbin",
    description = "clean binaries",
    execute     = function ()
        print("clean the build...")
        os.rmdir("./bin/*")
        print("done.")
    end
}