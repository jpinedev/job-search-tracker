workspace "JobSearchTracker"
    configurations { "Debug", "Release" }

project "TrackerCommon"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    
    files { "common/**.h", "common/**.cpp" }

project "JobSearchTracker"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    
    files { "tracker/**.h", "tracker/**.cpp" }

    links { "TrackerCommon" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "system:macosx" }
        includedirs { "/usr/local/include" }

    filter { "system:linux" }
        includedirs { "/usr/local/include" }
    
project "TrackingExporter"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    
    files { "exporter/**.h", "exporter/**.cpp" }

    links { "TrackerCommon" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "system:macosx" }
        includedirs { "/usr/local/include" }

    filter { "system:linux" }
        includedirs { "/usr/local/include" }

