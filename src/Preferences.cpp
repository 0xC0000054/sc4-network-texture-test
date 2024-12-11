////////////////////////////////////////////////////////////////////////
//
// This file is part of sc4-network-texture-test, a DLL Plugin for
// SimCity 4 that experiments with the network lot textures.
//
// Copyright (c) 2024 Nicholas Hayes
//
// This file is licensed under terms of the MIT License.
// See LICENSE.txt for more information.
//
////////////////////////////////////////////////////////////////////////

#include "Preferences.h"
#include "FileSystem.h"
#include "Logger.h"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"
#include "cIGZCOM.h"

namespace
{
	const char* BoolToString(bool value)
	{
		return value ? "true" : "false";
	}
}

Preferences::Preferences()
	: alwaysUseDirtBaseTextureForRail(false),
	  rhwVariation(0),
	  useNoneBaseTextureForResLowDensity(false)
{
}

void Preferences::Load()
{
	Logger& logger = Logger::GetInstance();

	try
	{
		std::filesystem::path path = FileSystem::GetConfigFilePath();

		std::ifstream stream(path, std::ifstream::in);

		if (stream)
		{
			boost::property_tree::ptree tree;

			boost::property_tree::ini_parser::read_ini(stream, tree);

			alwaysUseDirtBaseTextureForRail = tree.get<bool>("NetworkTexture.AlwaysUseDirtBaseTextureForRail");
			rhwVariation = tree.get<uint8_t>("NetworkTexture.RHWVariation") & 0xF;
			useNoneBaseTextureForResLowDensity =tree.get<bool>("NetworkTexture.UseNoneBaseTextureForResLowDensity");

			logger.WriteLineFormatted(
				LogLevel::Info,
				"Preferences: AlwaysUseDirtBaseTextureForRail=%s RHWVariation=0x%x UseNoneBaseTextureForResLowDensity=%s",
				BoolToString(alwaysUseDirtBaseTextureForRail),
				rhwVariation,
				BoolToString(useNoneBaseTextureForResLowDensity));
		}
		else
		{
			logger.WriteLine(LogLevel::Error, "Failed to open the DLL INI file.");
		}
	}
	catch (const std::exception& e)
	{
		logger.WriteLineFormatted(
			LogLevel::Error,
			"Error reading the DLL INI file: %s",
			e.what());
	}
}

bool Preferences::AlwaysUseDirtBaseTextureForRail() const
{
	return alwaysUseDirtBaseTextureForRail;
}

uint8_t Preferences::RHWVariation() const
{
	return rhwVariation;
}

bool Preferences::UseNoneBaseTextureForResLowDensity() const
{
	return useNoneBaseTextureForResLowDensity;
}
