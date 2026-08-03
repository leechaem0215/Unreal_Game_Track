#include "Input.h"
#include <cassert>
#include <Windows.h>

namespace Craft
{
	// static 변수 초기화
	Input* Input::instance = nullptr;

	Craft::Input::Input()
	{
		// 시작할 때 instance 값은 null 이어야 함.
		assert(!instance && "instance should be null here.");
		instance = this;
	}

	bool Craft::Input::GetKeyDown(int keyCode) const
	{
		return !keyStates[keyCode].wasKeyDown && keyStates[keyCode].isKeyDown;
	}

	bool Craft::Input::GetKeyUp(int keyCode) const
	{
		return keyStates[keyCode].wasKeyDown && !keyStates[keyCode].isKeyDown;
	}

	bool Craft::Input::GetKey(int keyCode) const
	{
		return keyStates[keyCode].isKeyDown;
	}

	Input& Craft::Input::Get()
	{
		// 여기에서 instance는 null 이면 안됨
		assert(instance && "instance should be null here.");
		return *instance;
	}

	void Craft::Input::ProcessInput()
	{
		// 현재 프레임에 키 입력이 발생했는지 확인
		for (int ix = 0; ix < keyCount; ++ix)
		{
			// 키 눌림 여부 저장
			// 0x8000은 최상위 비트
			keyStates[ix].isKeyDown = ((GetAsyncKeyState(ix) & 0x8000) != 0);
		}
	}

	void Craft::Input::SavePrevioutStates()
	{
		// 이전 프레임 입력 값 저장
		for (KeyState& state : keyStates)
		{
			state.wasKeyDown = state.isKeyDown;
		}
	}

}
