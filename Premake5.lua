workspace "DurnaEngine"
	architecture "x64"
	startproject "Game"

	configurations
	{
	"Debug",
	"Release",
	"Dist"
	}
	
-- IncludeDir = {}
-- IncludeDir[GLFW] = "ThirdParty/Header"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	
----------------------------------------------
---------- Engine -----------------------
----------------------------------------------
	
project "Engine"
	location "Engine"
	kind "Staticlib"
	language "c++"
	cppdialect "c++17"
	staticruntime "on"
	
	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "DurnaPCH.h"
	pchsource "Engine/Source/DurnaPCH.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Source/ThirdParty/Glad/glad.c"
	}
	
	libdirs
	{
		"ThirdParty/Library/**"
	}
	
	includedirs
	{
		"%{prj.name}/Source",
		"ThirdParty/Header"
	}
	
	links
	{
--		"glfw3.lib",
		"glfw3_mt.lib",
		"opengl32.lib"
	}
	
	filter "files:**.c"
		flags {"NoPCH"}
	
	filter "configurations:Debug"
		defines
		{
			"DRN_DEBUG"
		}
			
		runtime "Debug"
		symbols "on"			
		
	filter "configurations:Release"
		defines
		{
			"DRN_RELEASE"
		}
		
		runtime "Release"
		optimize "on"
				
	filter "configurations:Dist"
		defines
		{
			"DRN_DIST"
		}
		
		runtime "Release"
		optimize "on"


----------------------------------------------
---------- Game ---------------------------
----------------------------------------------
	
project "Game"
	location "Game"
	kind "ConsoleApp"
	language "c++"
	cppdialect "c++17"
	staticruntime "on"
	
	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}
	
	includedirs
	{
		"Engine/Source"
	}
	
	links "Engine"
	
	filter "configurations:Debug"
		defines
		{
			"DRN_DEBUG"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"DRN_RELEASE"
		}
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines
		{
			"DRN_DIST"
		}
		runtime "Release"
		optimize "on"