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

#pragma once
#include "cISC4BuildingOccupant.h"
#include "cISC4ZoneManager.h"

namespace NetworkLotTextures
{
	struct BaseTexturesByWealth
	{
		uint32_t none;
		uint32_t low;
		uint32_t medium;
		uint32_t high;
	};

	uint32_t GetBaseTexture(cISC4ZoneManager::ZoneType zone, cISC4BuildingOccupant::WealthType wealth);
	BaseTexturesByWealth* GetBaseTexturesForZone(cISC4ZoneManager::ZoneType zone);

	// For variations, the game uses the same texture for None and Low

	struct VariationByWealth
	{
		uint8_t low;
		uint8_t medium;
		uint8_t high;
	};

	uint8_t GetVariation(cISC4ZoneManager::ZoneType zone, cISC4BuildingOccupant::WealthType wealth);
	VariationByWealth* GetVariationsForZone(cISC4ZoneManager::ZoneType zone);
}