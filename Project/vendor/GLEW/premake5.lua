project "GLEW"
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"
    staticruntime "off"

    targetdir ("../../../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../../../bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "v2_2_0/src/**.c",
        "v2_2_0/include/**.h"
    }

    includedirs {
        "v2_2_0/include"
    }

    defines {
        "GLEW_STATIC"
    }

    filter "system:windows"
        systemversion "latest"
        characterset "MBCS"

    filter "system:macosx"
        xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "on"
