#pragma once
#include "../../Includes.h"
#include "GameWorld.h"

class GameObject
{
public:
	WinProcess *GameProcess;
	uint64_t Address;

	GameObject(WinProcess *GameProc, uint64_t Addr)
	{
		GameProcess = GameProc;
		Address = Addr;
	}

	std::string GetGameObjectName()
	{
		std::string result;
		uint64_t GameObjectNameAddr = GameProcess->Read<uint64_t>(Address + 0x60);

		for (int i = 0; i <= 100; i++)
		{
			char CurrentChar = GameProcess->Read<char>(GameObjectNameAddr + i);

			if (CurrentChar == '\0')
				break;

			result.push_back(CurrentChar);
		}
		return result;
	}

	uint64_t GetGameComponent()
	{
		uint64_t ObjectClass = GameProcess->Read<uint64_t>(Address + 0x30);
		uint64_t Entity = GameProcess->Read<uint64_t>(ObjectClass + 0x18);
		uint64_t BaseEntity = GameProcess->Read<uint64_t>(Entity + 0x28);
		return BaseEntity;
	}

	GameWorld GetLocalGameWorld()
	{
		return GameWorld(GetGameComponent());
	}

};