workspace "DurnaEngine"
	architecture "x64"
	startproject "Game"

	configurations
	{
	"DebugEditor",
	"Debug",
	"Release",
	"Dist"
	}
	
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

	links "ImGui"

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
		"ThirdParty/Header",
		"ImGui"
	}
	
	links
	{
		"glfw3_mt.lib",
		"opengl32.lib",
		"assimp-vc142-mt.lib"
	}
	
	filter "files:**.c"
		flags {"NoPCH"}
	
	filter "configurations:DebugEditor"
		defines
		{
			"DRN_DEBUG",
			"WITH_EDITOR"
		}
			
		runtime "Debug"
		symbols "on"	

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
	links "ImGui"
	
	postbuildcommands 
	{
		"{COPY} ../ThirdParty/Library/assimp/assimp-vc142-mt.dll ../Bin/" .. outputdir .. "/%{prj.name}",
		"{RMDIR} ../Bin/" .. outputdir .. "/Content/",
		"{COPY} ../Content/ ../Bin/" .. outputdir .. "/Content/" 
	}
	
	filter "configurations:DebugEditor"
		defines
		{
			"DRN_DEBUG",
			"WITH_EDITOR"
		}
		runtime "Debug"
		symbols "on"	
	
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
		
		
include "ImGui/premake5.lua"