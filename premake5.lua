workspace "CrashCourse"
    architecture "x86_64"
    language "C++"
    configurations {"Debug", "Release"}
    startproject "Project"

-- Clean Function --
newaction {
    trigger = "clean",
    description = "Cleans projects configurations",
    onStart = function()
        print("> Starting cleasing...")
    end,
    onWorkspace = function(wks)
        printf(">> Removing workspace data '%s'", wks.name)

        -- Xcode
        os.rmdir(wks.name..".xcworkspace")
    end,

    onProject = function(prj)
        printf(">> Removing projects data '%s'", prj.name)

        -- prj.location includes the full path

        -- Windows Visual Studio
        os.remove(prj.location.."/*.vcxproj")
        os.remove(prj.location.."/*.vcxproj.user")

        -- Xcode
        os.rmdir(prj.location.."/"..prj.name..".xcodeproj")

    end,

    execute = function ()

        os.rmdir("./bin")

        -- Windows Visual Studio
        os.rmdir("./bin-int")
        os.rmdir(".vs")
        os.remove("./*.sln")

        local hostOS = os.host()
        if (hostOS == "macosx") then
            os.execute("dot_clean .")
        elseif (hostOS == "windows") then
            os.execute("del /s /q /f /a ._.*")
        end
    end,

    onEnd = function()
        print("> Done.")
    end
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "Project/vendor/GLEW"
group ""

project "Project"
    location "Project"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    debugdir ("bin/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/GLEW/v2_2_0/include",
        "%{prj.name}/vendor/GLM/v0_9_9_8/include",
        "%{prj.name}/vendor/STB/include"
    }

    links {
        "GLEW"
    }

    filter "system:macosx"
        xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

        postbuildcommands
        {
            ("{COPY} ./shaders \"../bin/" .. outputdir .. "/%{prj.name}/\""),
            ("{COPY} ./textures \"../bin/" .. outputdir .. "/%{prj.name}/\""),
            ("{COPY} ./models \"../bin/" .. outputdir .. "/%{prj.name}/\"")
        }

    filter "system:windows"
        systemversion "latest"

        defines {
            "__WINDOWS__",
            "GLEW_STATIC"
        }

        links {
            "opengl32",
            "glfw3"
        }

        libdirs {
            "%{prj.name}/vendor/GLFW/Windows/lib/x64"
        }

        includedirs {
            "%{prj.name}/vendor/GLFW/Windows/include",
            "%{prj.name}/vendor/ASSIMP/include"
        }

        postbuildcommands
        {
            ("{COPY} ./vendor/GLFW/Windows/lib/x64/glfw3.dll \"../bin/" .. outputdir .. "/%{prj.name}/\""),
            ("{COPY} ./shaders \"../bin/" .. outputdir .. "/%{prj.name}/shaders/\""),
            ("{COPY} ./textures \"../bin/" .. outputdir .. "/%{prj.name}/textures/\"")
        }

    filter "system:macosx"
        debugdir ""

        libdirs {
            "%{prj.name}/vendor/GLFW/MacOS/lib",
            "%{prj.name}/vendor/ASSIMP/MacOS/lib"
        }

        links {
            "glfw",
            "assimp",
            "/Library/Frameworks/OpenGL.framework"
        }

        includedirs {
            "%{prj.name}/vendor/GLFW/MacOS/include",
            "%{prj.name}/vendor/ASSIMP/MacOS/include"
        }

    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "on"
