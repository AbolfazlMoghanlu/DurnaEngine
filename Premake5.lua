workspace "DurnaEngine"
	architecture "x64"
	startproject "Sandbox"

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
---------- DurnaEngine -----------------------
----------------------------------------------
	
project "DurnaEngine"
	location "DurnaEngine"
	kind "Staticlib"
	language "c++"
	cppdialect "c++17"
	staticruntime "on"
	
	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "DurnaPCH.h"
	pchsource "DurnaEngine/Source/DurnaPCH.cpp"

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
		"glfw3.lib",
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
---------- Sandbox ---------------------------
----------------------------------------------
	
project "Sandbox"
	location "Sandbox"
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
		"DurnaEngine/Source"
	}
	
	links "DurnaEngine"
	
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