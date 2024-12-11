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
#include <type_traits>

enum NetworkTypeFlags : uint32_t
{
	NetworkTypeFlagNone = 0,
	NetworkTypeFlagRoad = 1 << 0,
	NetworkTypeFlagRail = 1 << 1,
	NetworkTypeFlagHighway = 1 << 2,
	NetworkTypeFlagStreet = 1 << 3,
	NetworkTypeFlagWaterPipe = 1 << 4,
	NetworkTypeFlagPowerPole = 1 << 5,
	NetworkTypeFlagAvenue = 1 << 6,
	NetworkTypeFlagSubway = 1 << 7,
	NetworkTypeFlagLightRail = 1 << 8,
	NetworkTypeFlagMonorail = 1 << 9,
	NetworkTypeFlagOneWayRoad = 1 << 10,
	NetworkTypeFlagDirtRoad = 1 << 11,
	NetworkTypeFlagGroundHighway = 1 << 12,

	NetworkTypeFlagAllNetworks = NetworkTypeFlagRoad | NetworkTypeFlagRail | NetworkTypeFlagHighway
	| NetworkTypeFlagStreet | NetworkTypeFlagWaterPipe | NetworkTypeFlagPowerPole | NetworkTypeFlagAvenue
	| NetworkTypeFlagSubway | NetworkTypeFlagLightRail | NetworkTypeFlagMonorail | NetworkTypeFlagOneWayRoad
	| NetworkTypeFlagDirtRoad | NetworkTypeFlagGroundHighway
};
