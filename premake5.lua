workspace "NoxData"
	architecture "x86_64"
	startproject "NoxData"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "NoxData"

if(os.isdir("Sandbox")) then
	include "Sandbox"
end