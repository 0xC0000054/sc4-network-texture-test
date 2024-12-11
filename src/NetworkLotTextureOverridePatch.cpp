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

#include "NetworkLotTextureOverridePatch.h"
#include "NetworkLotTextures.h"

void NetworkLotTextureOverridePatch::SetResLowDensityTexturesToNone()
{
	auto resLowDensityTextures = NetworkLotTextures::GetBaseTexturesForZone(cISC4ZoneManager::ZoneType::ResidentialLowDensity);

	resLowDensityTextures->none = 0;
	resLowDensityTextures->low = 0;
	resLowDensityTextures->medium = 0;
	resLowDensityTextures->high = 0;
}
