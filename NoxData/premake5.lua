project "NoxData"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs
	{
		"src"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

		filter "configurations:Debug"
		defines "ND_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ND_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ND_DIST"
		runtime "Release"
		optimize "on"