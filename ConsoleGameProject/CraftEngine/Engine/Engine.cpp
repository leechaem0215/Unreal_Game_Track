#include "Engine.h"
#include <iostream>
#include <Windows.h>

namespace Craft 
{
	Engine::Engine()
	{
	}
	Engine::~Engine()
	{
	}
	void Engine::Run()
	{
		// 시간 값 얻어올 수 있는 시계 필요
		// 고해상도 타이머 사용
		
		// 밀리세컨드 - 1/1000초 -> 해상도 1000.
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency); // 해상도 구하는 것
		
		// 현재 시간 읽기
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);

		// 프레임 계산을 위한 변수
		int64_t current = counter.QuadPart;
		int64_t previous = current;

		// 고정 프레임으로 만들기 위한 값.
		float oneFeametime = 1.0f / setting.framerate;


		// 엔진 루프
		while (true) 
		{
			// 종료 조건 처리
			if (isQuit)
			{
				break;
			}
			// 프레임 처리

			// 입력 처리
			ProcessInput();

			// 프레임 시간 계산
			// 1. 현재 시간 읽기.
			QueryPerformanceCounter(&counter);
			current = counter.QuadPart;
			// 2. (현재 시간 - 이전 시간) / 시간 단위(해상도).
			// -> 초단위로 변환
			// 예) 밀리세컨드(1/1000초). 200밀리세컨드(0.2초)
			float deltaTime = static_cast<float>(current - previous)
				/ static_cast<float>(frequency.QuadPart);
			
			if (deltaTime >= oneFeametime) {

				// 게임 이벤트 함수 호출
				OnInitialized();

				// 게임 이벤트의 초기화 함수 (1번만 호출)
				BeginPlay();

				// 게임 업데이트
				Tick(deltaTime);

				// 화면 그리기
				Draw();

				// 다음 프레임을 위해 입력상태 저장
				SavePreviousInputStates();

				// 현재 시간을 이전 시간으로 저장.
				previous = current;
			}
		}
		// 종료 처리 함수 호출
		Shutdown();
	}
	void Engine::Quit()
	{
		// 엔진 종료 플래그 설정
		isQuit = true;
	
	}
	void Engine::ProcessInput()
	{
	}
	void Engine::OnInitialized()
	{
	}
	void Engine::BeginPlay()
	{
	}
	void Engine::Tick(float deltaTime)
	{
		// Todo : deltaTime 출력
		std::cout
			<< "Engine::Tick() - deltaTime: "
			<< deltaTime
			<< " | FPS: "  // 순간 프레임
			<< (1.0f / deltaTime)
			<< "\n";
	}
	void Engine::Draw()
	{
	}
	void Engine::SavePreviousInputStates()
	{
	}
	void Engine::Shutdown()
	{
	}
}