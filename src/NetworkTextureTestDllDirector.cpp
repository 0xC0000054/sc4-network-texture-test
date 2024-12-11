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

#include "cSC4NetworkLotManagerHooks.h"
#include "FileSystem.h"
#include "GlobalPointers.h"
#include "Logger.h"
#include "NetworkLotTextureOverridePatch.h"
#include "SC4VersionDetection.h"
#include "version.h"
#include "cIGZCOM.h"
#include "cIGZFrameWork.h"
#include "cRZAutoRefCount.h"
#include "cRZBaseString.h"
#include "cRZCOMDllDirector.h"
#include "GZServPtrs.h"

static constexpr uint32_t kNetworkTextureTestDllDirector = 0x8E7C4583;

const Preferences* spPreferences = nullptr;

class NetworkTextureTestDllDirector final : public cRZCOMDllDirector
{
public:
	NetworkTextureTestDllDirector()
	{
		spPreferences = &preferences;

		Logger& logger = Logger::GetInstance();
		logger.Init(FileSystem::GetLogFilePath(), LogLevel::Error);
		logger.WriteLogFileHeader("SC4NetworkTextureTest v" PLUGIN_VERSION_STR);
	}

	uint32_t GetDirectorID() const
	{
		return kNetworkTextureTestDllDirector;
	}

	bool OnStart(cIGZCOM* pCOM)
	{
		Logger& logger = Logger::GetInstance();

		const uint16_t gameVersion = SC4VersionDetection::GetGameVersion();

		if (gameVersion == 641)
		{
			preferences.Load();

			cSC4NetworkLotManagerHooks::Install();
			logger.WriteLine(LogLevel::Info, "Installed the NetworkLotManager hooks.");

			if (preferences.UseNoneBaseTextureForResLowDensity())
			{
				NetworkLotTextureOverridePatch::SetResLowDensityTexturesToNone();
				logger.WriteLine(LogLevel::Info, "Set the Res. low density network wealth textures to none.");
			}
		}
		else
		{
			logger.WriteLineFormatted(LogLevel::Error, "Unsupported game version %u", gameVersion);
		}

		return true;
	}

private:
	Preferences preferences;
};

cRZCOMDllDirector* RZGetCOMDllDirector() {
	static NetworkTextureTestDllDirector sDirector;
	return &sDirector;
}