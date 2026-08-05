#pragma once

#include <Core/Core.h>
#include <memory> // 스마트 포인터 사용을 위해

// CraftEngine 프로젝트 안의 클래스는 Craft 네임 스페이스 사용.
namespace Craft {
	// 전방 선언
	class Level;
	class Input; // 포인터 관리하기 위해서
	class Renderer; // 포인터로 다룰거임

	// 메인 엔진 클래스
	// 엔진 루프를 제공
	// 게임 엔진의 핵심 기능 제공.
	class CRAFT_API Engine
	{
		// 엔진 설정 (데이터).
		struct Setting
		{
			// 목표 프레임 수 (초당 프레임).
			float framerate = 0.0f;

			// 사용할 콘솔 화면 너비.
			int width = 0;

			// 사용할 콘솔 화면 높이.
			int height = 0;
		};
	public:
		Engine();
		virtual ~Engine();

		// 엔진 실행 함수
		void Run();
		// 엔진 종료 함수
		void Quit();

		// 레벨 추가 요청 함수
		// std::is_base_if 하는일이 무엇인지
		// std::enable_if_t 하는 일이 무엇인지
		// typename = std::enable_if_t<std::is_base_of<Level, T>::value>>
		template<typename T,
			typename = std::enable_if_t<std::is_base_of<Level, T>::value>> // T 타입이 Level의 하위 레벨이 아니면 생성안됌
		void AddNewLevel()
		{
			// 추가 요청 레벨 객체 생성
			nextLevel = std::make_shared<T>();
		}

		// 전역 접근 함수
		static Engine& Get();

		// 화면 너비 필요할 때를 위해서
		// Getter, 화면 제어
		inline int GetWidth() const { return setting.width; }
		inline int GetHeight() const { return setting.height; }

	protected:
		// 입력 처리 함수 (입력 폴링)
		void ProcessInput();

		// 초기화 함수
		void  OnInitialized();

		// 게임 플레이 이벤트 함수
		
		// 게임 플레이 초기화 함수
		void BeginPlay();
		
		// 게임 플레이 업데이트 함수
		void Tick(float deltaTime);

		// 레벨 그리기 함수.
		void Draw();

		// 이전 프레임의 입력값과 비교할 것이 필요
		// 프레임 간 입력 값 저장을 위한 ㅣ함수
		void SavePreviousInputStates();

		// 엔진 종료 시 정리가 필요할 때 사용할 함수
		void Shutdown();

		// 엔진 설정 로드 함수.
		void LoadEngineSetting();

	protected:
		// 엔진 종료 요청 여부 플래그.
		bool isQuit = false;

		// 엔진 설정 함수
		Setting setting;
		
		// 전역 접근이 가능하도록 변수 선언
		static Engine* instance;

		// 메인 레벨
		std::shared_ptr<Level> mainLevel;

		// 추가 요청된 레벨
		std::shared_ptr<Level> nextLevel;
		
		// 입력 시스템 변수
		std::unique_ptr<Input> input;

		// 렌더러
		std::unique_ptr<Renderer> renderer;
	};

}
