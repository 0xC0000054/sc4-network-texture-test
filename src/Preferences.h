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
#include <cstdint>

class Preferences final
{
public:
	Preferences();

	void Load();

	bool AlwaysUseDirtBaseTextureForRail() const;
	uint8_t RHWVariation() const;
	bool UseNoneBaseTextureForResLowDensity() const;

private:
	bool alwaysUseDirtBaseTextureForRail;
	uint8_t rhwVariation;
	bool useNoneBaseTextureForResLowDensity;
};

