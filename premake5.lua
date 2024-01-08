workspace "JobSearchTracker"
    architecture "x86_64"
    startproject "JobSearchTracker"
    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }

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

project "TrackerCommon"
    location "TrackerCommon"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"

    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

project "JobSearchTracker"
    location "JobSearchTracker"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    
    includedirs { "." }    
    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }
    links { "TrackerCommon" }
    
project "TrackingExporter"
    location "TrackingExporter"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    
    includedirs { "." }    
    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }
    links { "TrackerCommon" }

