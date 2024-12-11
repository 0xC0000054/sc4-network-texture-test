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
#include "cISC4BuildingOccupant.h"
#include "cISC4NetworkOccupant.h"
#include "cISC4ZoneManager.h"
#include "GlobalPointers.h"
#include "NetworkLotTextures.h"
#include "NetworkTypeFlags.h"
#include "Patcher.h"

namespace
{
	void SetBaseTextureAndVariation(
		cISC4NetworkOccupant* pNetworkOccupant,
		cISC4ZoneManager::ZoneType zoneType,
		cISC4BuildingOccupant::WealthType wealthType)
	{
		constexpr uint32_t kDirtBaseTextureID = 0x08400000;

		const uint32_t networkFlags = pNetworkOccupant->GetNetworkFlag();
		const NetworkTypeFlags networkTypeFlags = static_cast<NetworkTypeFlags>(networkFlags & NetworkTypeFlagAllNetworks);

		uint32_t baseTextureID = 0;

		if ((networkTypeFlags & NetworkTypeFlagRail) != 0)
		{
			// The rail network always uses either the dirt or none base texture.
			// By default, we use empty. But provide the option to always use dirt.
			if (spPreferences->AlwaysUseDirtBaseTextureForRail())
			{
				baseTextureID = kDirtBaseTextureID;
			}
		}
		else
		{
			// The RHW (DirtRoad) network always uses the none base texture.
			if ((networkTypeFlags & NetworkTypeFlagDirtRoad) == 0)
			{
				// OneWayRoad has been added to the wealth network flags to prevent it
				// from being assigned a dirt texture.
				// For some reason, the Maxis code works without that flag being present.

				constexpr uint32_t WealthTextureNetworkFlags =
					NetworkTypeFlagRoad
					| NetworkTypeFlagHighway
					| NetworkTypeFlagStreet
					| NetworkTypeFlagOneWayRoad;

				if ((networkTypeFlags & WealthTextureNetworkFlags) != 0)
				{
					baseTextureID = NetworkLotTextures::GetBaseTexture(zoneType, wealthType);
				}
				else
				{
					baseTextureID = zoneType != cISC4ZoneManager::ZoneType::None ? kDirtBaseTextureID : 0;
				}
			}
		}

		pNetworkOccupant->SetUnderTexture(baseTextureID);

		if (baseTextureID != 0)
		{
			pNetworkOccupant->SetNetworkFlag(0x06000000);
		}

		uint8_t variation = 0;

		if ((networkTypeFlags & NetworkTypeFlagDirtRoad) != 0)
		{
			// RHW (DirtRoad) uses a single variation.
			variation = spPreferences->RHWVariation();
		}
		else
		{
			variation = NetworkLotTextures::GetVariation(zoneType, wealthType);
		}

		pNetworkOccupant->SetVariation(variation);
	}

	static constexpr uint32_t UpdateRoadStyle_SetBaseTextureAndVariation_Continue = 0x60F5E7;

	void NAKED_FUN UpdateRoadStyle_SetBaseTextureAndVariation_Hook()
	{
		__asm
		{
			// We do not need to preserve any registers.
			push eax // wealth
			push ebx // zoneType
			push esi // cISC4NetworkOccupant
			call SetBaseTextureAndVariation // (cdecl)
			add esp, 12
			mov ecx, UpdateRoadStyle_SetBaseTextureAndVariation_Continue
			jmp ecx
		}
	}
}

void cSC4NetworkLotManagerHooks::Install()
{
	Patcher::InstallJump(0x60F580, reinterpret_cast<uintptr_t>(&UpdateRoadStyle_SetBaseTextureAndVariation_Hook));
}
