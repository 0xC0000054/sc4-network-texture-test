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

#include "NetworkLotTextures.h"

NetworkLotTextures::BaseTexturesByWealth* const baseTextureArrayStart = reinterpret_cast<NetworkLotTextures::BaseTexturesByWealth*>(0xAA7758);
NetworkLotTextures::VariationByWealth* const variationArrayStart = reinterpret_cast<NetworkLotTextures::VariationByWealth*>(0xAA7728);

uint32_t NetworkLotTextures::GetBaseTexture(cISC4ZoneManager::ZoneType zone, cISC4BuildingOccupant::WealthType wealth)
{
	uint32_t baseTextureID = 0;

	const BaseTexturesByWealth* zoneBaseTextures = GetBaseTexturesForZone(zone);

	switch (wealth)
	{
	case cISC4BuildingOccupant::WealthType::None:
		baseTextureID = zoneBaseTextures->none;
		break;
	case cISC4BuildingOccupant::WealthType::Low:
		baseTextureID = zoneBaseTextures->low;
		break;
	case cISC4BuildingOccupant::WealthType::Medium:
		baseTextureID = zoneBaseTextures->medium;
		break;
	case cISC4BuildingOccupant::WealthType::High:
		baseTextureID = zoneBaseTextures->high;
		break;
	}

	return baseTextureID;
}

NetworkLotTextures::BaseTexturesByWealth* NetworkLotTextures::GetBaseTexturesForZone(cISC4ZoneManager::ZoneType zone)
{
	return baseTextureArrayStart + static_cast<uint32_t>(zone);
}

uint8_t NetworkLotTextures::GetVariation(cISC4ZoneManager::ZoneType zone, cISC4BuildingOccupant::WealthType wealth)
{
	uint8_t variation = 0;

	const VariationByWealth* zoneVariations = GetVariationsForZone(zone);

	switch (wealth)
	{
	case cISC4BuildingOccupant::WealthType::None:
	case cISC4BuildingOccupant::WealthType::Low:
		variation = zoneVariations->low;
		break;
	case cISC4BuildingOccupant::WealthType::Medium:
		variation = zoneVariations->medium;
		break;
	case cISC4BuildingOccupant::WealthType::High:
		variation = zoneVariations->high;
		break;
	}

	return variation;
}

NetworkLotTextures::VariationByWealth* NetworkLotTextures::GetVariationsForZone(cISC4ZoneManager::ZoneType zone)
{
	return variationArrayStart + static_cast<uint32_t>(zone);
}
