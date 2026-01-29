include("premake/utils")

SDK_PATH = os.getenv("HL2SDKCS2")
MM_PATH = os.getenv("MMSOURCE112")

if(SDK_PATH == nil) then
	error("INVALID HL2SDK PATH")
end

if(MM_PATH == nil) then
	error("INVALID METAMOD PATH")
end

workspace "HammerIdFix"
	configurations { "Debug", "Release" }
	platforms {
		"win64",
		"linux64"
	}
	location "build"

project "HammerIdFix"
	kind "SharedLib"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	location "build/HammerIdFix"
	visibility  "Hidden"
	targetprefix ""

	files { "src/**.h", "src/**.cpp" }

	vpaths {
		["Headers/*"] = "**.h",
		["Sources/*"] = "**.cpp"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	filter "system:windows"
		cppdialect "c++20"
		include("premake/mm-windows.lua")

	filter "system:linux"
		cppdialect "c++2a"
		include("premake/mm-linux.lua")
		links { "pthread", "z"}

	filter {}

	defines { "META_IS_SOURCE2" }

	includedirs "src"

	vectorextensions "sse"
	strictaliasing "Off"

	flags { "MultiProcessorCompile", "Verbose" }
	pic "On"