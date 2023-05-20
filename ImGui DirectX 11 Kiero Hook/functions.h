#pragma once
#include "vec.h"
#include "vec2.h"
#include <string>
#include "il2cpp_resolver.hpp"
#include "Lists.hpp"
#include <intrin.h>

namespace Functions
{
#pragma region Hooks
	void(UNITY_CALLING_CONVENTION SetTargetRecoil)(CombatMaster_Battle_Gameplay_Player_PlayerMovement_o*, float);
	void SetTargetRecoil_hk(CombatMaster_Battle_Gameplay_Player_PlayerMovement_o* movement, float recoil)
	{
		if (vars::recoileditor)
		{
			recoil = vars::recoiledited; // 0.0f
		}

		return SetTargetRecoil(movement, recoil);
	}
#pragma endregion

#pragma region Game Functions
	// UnityEngine_Camera$$Get_Main
	Unity::CCamera* GetMainCamera()
	{
		Unity::CCamera* (UNITY_CALLING_CONVENTION get_main)();
		return reinterpret_cast<decltype(get_main)>(sdk::GameAssembly + 0x0)();
	}
#pragma endregion

#pragma region Custom Functions
	bool worldtoscreen(Unity::Vector3 world, Vector2& screen)
	{
		Unity::CCamera* CameraMain = Unity::Camera::GetMain(); // Get The Main Camera
		if (!CameraMain) {
			return false;
		}

		//Unity::Vector3 buffer = WorldToScreenPoint(CameraMain, world, 2);

		Unity::Vector3 buffer = CameraMain->CallMethodSafe<Unity::Vector3>("WorldToScreenPoint", world, Unity::eye::mono); // Call the worldtoscren function using monoeye (2)

		if (buffer.x > vars::screen_size.x || buffer.y > vars::screen_size.y || buffer.x < 0 || buffer.y < 0 || buffer.z < 0) // check if point is on screen
		{
			return false;
		}

		if (buffer.z > 0.0f) // Check if point is in view
		{
			screen = Vector2(buffer.x, vars::screen_size.y - buffer.y);
		}

		if (screen.x > 0 || screen.y > 0) // Check if point is in view
		{
			return true;
		}
	}
#pragma endregion
}