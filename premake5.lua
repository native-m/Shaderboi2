-- premake5.lua

PROJECT_NAME = "Shaderboi"

act = ""
if _ACTION then
	act = _ACTION
end

if act ~= "vs2015" and
	act ~= "vs2017" and
	act ~= "vs2019" and
	act ~= "clean" and 
	act ~= "cleanbin" and
	act ~= "cleanall" and
	act ~= "" then
	print("You can't build " .. PROJECT_NAME .. " with this action: " .. act)
	print("Please choose one of these actions: vs2015, vs2017, vs2019")
	os.exit() -- exit the script
end

newaction {
	trigger = "clean",
	description = "clean all build files",
	execute = function()
		print("Cleaning build files... this may take a while")
		os.rmdir("./build")
		print("Done!")
	end
}

newaction {
	trigger = "cleanbin",
	description = "clean all compiled binary files",
	execute = function()
		print("Cleaning compiled binary files... this may take a while")
		os.rmdir("./bin")
		print("Done!")
	end
}

newaction {
	trigger = "cleanall",
	description = "clean all build & compiled binary files",
	execute = function()
		print("Cleaning build & compiled binary files... this may take a while")
		os.rmdir("./build")
		os.rmdir("./bin")
		print("Done!")
	end
}

function isFileExist(path)
	if type(path) ~= "string" then
		return false
	end

	file = io.open(path, "r")
	if file then
		io.close(file)
		return true
	end

	return false
end

-- automatically detect visual studio version
-- and check if visual c++ is installed
if act == "" then
	print("Please specify action...")
	os.exit()
end

-- [ WORKSPACE & PROJECT SETUP ] --

workspace(PROJECT_NAME .. "_" .. act)
	location("build/" .. act)
	configurations { "Debug", "Release" }
	platforms { "x86", "x64" }
	flags { "MultiProcessorCompile", "NoPCH" }

project(PROJECT_NAME .. "_" .. act)
	kind "ConsoleApp"
	language "C++"
	targetdir("bin/" .. act .. "/%{cfg.buildcfg}_%{cfg.platform}")

	includedirs { 
		"deps/freetype/include",
		"deps/sdl/include",
		"deps/glad/include",
		"deps/imgui",
		"deps/ImGuiColorTextEdit"
	}

	vpaths {
		["Deps/freetype"] = {
			"deps/freetype/include/**.h"
		},
		["Deps/imgui"] = {
			"deps/imgui/*.h",
			"deps/imgui/*.cpp"
		},
		["Deps/glad"] = {
			"deps/glad/include/glad/*.h",
			"deps/glad/include/KHR/*.h",
			"deps/glad/src/*.c"
		},
		["Deps/ImGuiColorTextEdit"] = {
			"deps/ImGuiColorTextEdit/*.h",
			"deps/ImGuiColorTextEdit/*.cpp"
		},
		["Headers/*"] = { "src/**.h", "src/**.hxx", "src/**.hpp" },
		["Sources/*"] = { "src/**.cpp", "src/**.cxx" }
	}

	files {
		"deps/imgui/*.h",
		"deps/imgui/*.cpp",
		"deps/imgui/misc/freetype/*.h",
		"deps/imgui/misc/freetype/*.cpp",
		"deps/glad/include/glad/*.h",
		"deps/glad/include/KHR/*.h",
		"deps/glad/src/**.c",
		"deps/ImGuiColorTextEdit/*.h",
		"deps/ImGuiColorTextEdit/*.cpp",
		"src/**.h",
		"src/**.cpp"
	}

	links {
		"deps/sdl/lib/%{cfg.platform}/SDL2.lib",
		"deps/sdl/lib/%{cfg.platform}/SDL2main.lib",
		"deps/freetype/lib/%{cfg.platform}/freetype.lib"
	}

	filter { "configurations:Debug", "platforms:x86" }
		architecture "x32"
		defines { "_DEBUG=1", "_PLATFORM_X64=0" }

	filter { "configurations:Debug", "platforms:x64" }
		architecture "x64"
		defines { "_DEBUG=1", "_PLATFORM_X64=1" }

	filter { "configurations:Release", "platforms:x86" }
		architecture "x32"
		defines { "_PLATFORM_X64=0" }
		
	filter { "configurations:Release", "platforms:x64" }
		architecture "x64"
		defines { "_PLATFORM_X64=1" }

	filter "configurations:Debug"
		symbols "On"
		optimize "Debug"

	filter "configurations:Release"
		symbols "Off"
		optimize "Speed"

	filter {}

	postbuildcommands {
		'{COPY} ../../deps/freetype/lib/%{cfg.platform}/freetype.dll %{cfg.targetdir}',
		'{COPY} ../../deps/sdl/lib/%{cfg.platform}/SDL2.dll %{cfg.targetdir}',
		'{COPY} ../../res %{cfg.targetdir}'
	}