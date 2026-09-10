#include "Engine.h"
#include <Level/Level.h>
#include <Input/Input.h>
#include <Render/Renderer.h>
#include <Physics/CollisionSystem.h>
#include "Sound.h"

#include <iostream>
#include <Windows.h>
#include <cassert>
#include <stdexcept>
#include <system_error>
#include <climits>

namespace Craft 
{
	// 전역 변수 초기화
	Engine* Engine::instance = nullptr;

	Engine::Engine() : Engine(0, 0) {}

	Engine::Engine(int width, int height)
	{
		// instance 초기화
		assert(!instance && "anoter instance is not null");
		instance = this;

		// 엔진 설정 로드
        LoadEngineSetting();
        // (0, 0) keeps the configured size for existing Engine() callers.
        if (width != 0 || height != 0)
        {
            if (width <= 0 || height <= 0 || width > SHRT_MAX || height > SHRT_MAX)
                throw std::invalid_argument("Engine width and height must be positive console dimensions");
            setting.width = width;
            setting.height = height;
        }

		SetConsoleFontSize(setting.fontWidth, setting.fontHeight);
		SetConsoleSize(setting.width, setting.height);

		// 입력 객체 생성
		input = std::make_unique<Input>();

		// 렌더러 객체 생성
		renderer = std::make_unique<Renderer>(
			Vector2(setting.width, setting.height)
		);

		// 콜리전 시스템 객체 생성
		collisionSystem = std::make_unique<CollisionSystem>();

		// 사운드 시스템 객체 생성
		sound = std::make_unique<Sound>();
	}

	Engine::~Engine()
	{
		instance = nullptr;
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
		float oneFrameTime= 1.0f / setting.framerate;


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
			
			// 고정 프레임 처리.
			// 프레임 사이에 걸린 시간이 목표 시간보다 더 많이 지났으면
			// 프레임 처리.
			if (deltaTime >= oneFrameTime) {

				// 게임 이벤트 함수 호출
				OnInitialized();

				// 게임 이벤트의 초기화 함수 (1번만 호출)
				BeginPlay();

				// 게임 업데이트
				Tick(deltaTime);

				// 충돌 처리
				ProcessCollision();

				// 화면 그리기
				Draw();

				// 이 위까지 호출이 완료되면 프레임 처리 완료됨

				// 레벨 전환 처리
				if (nextLevel)
				{
					// 기존 레벨 정리
					if (mainLevel)
					{
						mainLevel.reset();
					}
					// 추가 요청된 레벨을 메인 레벨로 설정
					mainLevel = nextLevel;

					// 포인터 정리
					nextLevel.reset(); // reset : 포인터가 가리키는곳 null 해주는거
				}
				
				// 추가/제거 요청된 액터 정리
				if (mainLevel)
				{
					mainLevel->ProcessAddAndDestroyActors();
					mainLevel->SavePreviousActorStates(); // 액터의 이전 상태 저장 처리

					//mainLevel->ProcessAddAndDestroyActors();
				}

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

	
	void Engine::PlayOneShot(const std::string& filename)
	{
		if (!sound) 
		{
			return;
		}
		// 사운드 시스템 함수 호출
		sound->PlayOneShot(std::string("../Assets/Sound/") + filename);
	}

	void Engine::PlayBackgroundMusic(const std::string& filename)
	{
		if (!sound)
		{
			return;
		}
		// 사운드 시스템 함수 호출
		sound->PlayBackgroundMusic(std::string("../Assets/Sound/") + filename);
	}

	void Engine::StopBackgroundMusic()
	{
		if (!sound)
		{
			return;
		}
		sound->StopBackgroundMusic();
	}

	Engine& Engine::Get()
	{
		// 검증 - 어서트
		// 무조건 (필수로) 통화해야하는 조건이 있을 때 사용
		// 디버그 모드에서만 동작
		assert(instance && "instance is null");
		
		return *instance;
	}
	void Engine::ProcessInput()
	{
		assert(input && "input should not be null here");
		if (!input)
		{
			return;
		}
		input->ProcessInput();
	}
	void Engine::OnInitialized()
	{
		// 레벨 초기화 처리
		// 예외처리
		if (!mainLevel || mainLevel->HasInitialized()) 
		{
			return;
		}
		// 초기화 이벤트 호출
		mainLevel->OnInitialized();
	}

	void Engine::BeginPlay()
	{
		if (!mainLevel) 
		{
			return;
		}

		// 레벨에 이벤트 전달
		mainLevel->BeginPlay();

	}

	void Engine::Tick(float deltaTime)
	{
		if (!mainLevel) 
		{
			return;
		}
		mainLevel->Tick(deltaTime);
	}
	void Engine::Draw()
	{
		// 레벨이 먼저 그리기를 함
		if (!mainLevel)
		{
			return;
		}

		mainLevel->Draw();

		// 렌더러에 Draw 이벤트 호출.
		if (!renderer)
		{
			return;
		}

		renderer->Draw();
	}

	void Engine::ProcessCollision()
	{
		// 예외처리.
		if (!mainLevel || !collisionSystem)
		{
			return;
		}

		// 충돌 처리.
		// 의존성 주입(Dependency Injection).
		collisionSystem->ProcessCollision(mainLevel->actorList);
	}

	void Engine::SavePreviousInputStates()
	{
		assert(input && "input should not null here");
		if (!input)
		{
			return;
		}
		input->SavePreviousStates();
	}
	void Engine::Shutdown()
	{
	}

	void Engine::LoadEngineSetting()
	{
		// 파일 열기 (개행 문자 처리를 쉽게 텍스트 모드로 열기)
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt");

		// 예외처리
		if (!file)
		{
			std::cout << "Failed to open engine setting file.\n";

			// 디버그 모드에서 강제 중단 시키는 기능
			__debugbreak();
			return;
		}
		// 데이터 읽어오기
		const int bufferSize = 2048;
		char buffer[bufferSize] = {};

		size_t readSize = fread(buffer, sizeof(char), bufferSize, file);

		// 값 저장을 위해 서식 해석 (파싱-Parsing)
		// 문자열 자르기 (Split)
		char* context = nullptr;
		char* token = nullptr;
		
		// 파일에서 읽은 전체 문자열을 개행(\n) 문자 기준으로 처음 자르기
		token = strtok_s(buffer, "\n", &context);

		// 반복해서 자르기
		while (token)
		{
			// 공백 전까지 읽은 문자열을 저장할 변수
			char key[15] = {};
			// 포맷 지정한 문자열 읽기
			// 공백 문자를 만나면 그 전까지 읽어서 저장
			sscanf_s(token, "%s", key, 15);

			// 키 값을 비교해서 값 설정
			if (strcmp(key, "framerate") == 0) {
				sscanf_s(token, "framerate = %f", &setting.framerate);
			}
			else if (strcmp(key, "width") == 0) {
				sscanf_s(token, "width = %d", &setting.width);
			}
			else if (strcmp(key, "height") == 0) {
				sscanf_s(token, "height = %d", &setting.height);
			}
			else if (strcmp(key, "font_width") == 0) {
				sscanf_s(token, "font_width = %d", &setting.fontWidth);
			}
			else if (strcmp(key, "font_height") == 0) {
				sscanf_s(token, "font_height = %d", &setting.fontHeight);
			}


			// 나머지 문자열 자르기 (개행 문자 기준으로)
			token = strtok_s(nullptr, "\n", &context);
		}
		// 파일 닫기
		fclose(file);
		file = nullptr;
	}

    void Engine::SetConsoleFontSize(int width, int height)
    {
        if (width < 0 || height <= 0 || width > SHRT_MAX || height > SHRT_MAX)
            throw std::runtime_error("Invalid font_width/font_height in Config/Setting.txt");
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_FONT_INFOEX fontInfo{};
        fontInfo.cbSize = sizeof(fontInfo);
        if (!GetCurrentConsoleFontEx(console, FALSE, &fontInfo))
            throw std::system_error(GetLastError(), std::system_category(), "GetCurrentConsoleFontEx");
        fontInfo.dwFontSize = {static_cast<SHORT>(width), static_cast<SHORT>(height)};
        if (!SetCurrentConsoleFontEx(console, FALSE, &fontInfo))
            throw std::system_error(GetLastError(), std::system_category(), "SetCurrentConsoleFontEx");
    }

    void Engine::SetConsoleSize(int width, int height)
    {
        if (width <= 0 || height <= 0 || width > SHRT_MAX || height > SHRT_MAX)
            throw std::runtime_error("Invalid width/height in Config/Setting.txt");
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        const COORD largest = GetLargestConsoleWindowSize(console);
        if (width > largest.X || height > largest.Y)
            throw std::runtime_error("Console does not fit the display. Reduce width/height or font size in Config/Setting.txt.");
        // Window dimensions are character cells. Never pass them to MoveWindow (pixels).
        const SMALL_RECT temporary = {0, 0, 0, 0};
        const COORD size = {static_cast<SHORT>(width), static_cast<SHORT>(height)};
        const SMALL_RECT window = {0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1)};
        if (!SetConsoleWindowInfo(console, TRUE, &temporary)
            || !SetConsoleScreenBufferSize(console, size)
            || !SetConsoleWindowInfo(console, TRUE, &window))
            throw std::system_error(GetLastError(), std::system_category(), "SetConsoleSize");
    }
}
