#pragma once
#include <Core/Core.h>
#include <Actor/Actor.h>
#include <Core/CraftObject.h>
#include <memory> // std::unique_ptr / std::shared_ptr 사용
#include <vector> // std::vector 동적 배열

namespace Craft
{
	// 게임에 배치된 모든 액터를 관리하는 클래스.
	// public std::enable_shared_from_this<Level>
	// : shared_from_this() / weak_from_this() 사용하기 위해.
	// : shared_from_this() - this 포인터를 shared_ptr로 변환.
	// : weak_from_this() - this 포인터를 weak_ptr로 변환.
	class CRAFT_API Level :
		public CraftObject,
		public std::enable_shared_from_this<Level>
	{
	// 커스텀 타입 설정 
	TYPE_DECLARATIONS(Level, CraftObject)
	// friend 선언, 접근 가능하도록 예외 두는것
	friend class Engine; 

	public:
		Level();
		virtual ~Level();

		// 특정 레벨이 여러 게임객체 관리할거임
		// 초기화 함수
		virtual void OnInitialized(); // 게임플레이 들어가기전에 중간 초기화 함수

		//  게임 플레이 이벤트 함수
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// 액터 추가 함수 (템플릿)
		template<typename T, typename ...Args, // 가변인자
			typename = std::enable_if_t<std::is_base_of<Actor, T>::value>> // 액터타입이 아니면 무효화
		std::shared_ptr<T> SpawnActor(Args&& ...args) // 템플릿에서 가변인자 처리하는 방식임
		{
			// 새로운 액터 생성
			std::shared_ptr<T> newActor
				= std::make_shared<T>(std::forward<Args>(args)...);

			// 추가 요청 목록에 포함
			addRequestedActorList.emplace_back(newActor);

			// 오너십 설정. 
			newActor->SetOwner(weak_from_this()); // 레벨 입장에서 내가 생성 // 너를 생성한건 나라고 알려줘야함 newActor
			// 스마트 포인터가 this 를 넘기면 아무것도 안됌



			// 생성한 액터 반환
			return newActor;
		}

		// 액터 검색 함수 (템플릿)
		template<typename T, // 검색은 파라미터 받을 필요 없음
			typename = std::enable_if_t<std::is_base_of<Actor, T>::value>> // 액터타입이 아니면 무효화
			std::shared_ptr<T> FindActor() 
		{
			// 검색 - 형 변환
			for (const auto& actor : actorList)
			{
				// T 타입으로 형변환 시도
				// T 타입이 아닌 경우에는 null 반환
				std::shared_ptr<T> targetActor = std::dynamic_pointer_cast<T>(actor);
				if (targetActor)
				{
					return targetActor;
				}
			}

			// 못찾는 경우 null 반환
			return nullptr;
		}
		// Getter
		inline bool HasInitialized() const {return hasInitialized;}

	protected:
		// 이전 프레임에 추가/제거 요청된 액터 처리 함수
		void ProcessAddAndDestoryActors();

	protected:
		// 초기화 처리 여부 플래그.
		bool hasInitialized = false;

		// 레벨에 배치된 모든 액터
		std::vector<std::shared_ptr<Actor>> actorList;
		
		// 레벨에 추가 요청된 액터를 저장해두는 목록
		// 현재 프레임을 처리하는 과정에서 액터 추가 요청이 발생하면,
		//해당 액터를 바로 추가하면 기존 액터 처리에 문제가 발생할 수 있어서
		// 현재 프레임을 모두 처리한 후에 추가 요청된 액처를 actorList로 옮김.
		std::vector<std::shared_ptr<Actor>> addRequestedActorList;
	};
}