#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>// 타이머 사용

// 좌우로 이동/스페이스 키로 탄약을 발사하는 플레이어.
class Player : public Craft::Actor
{
	// 연사처리할거임
	// 발사 모드 (단발/연사)
	// 연사 처리할때는 타이머 기반으로 할거임, 연사 속도를 두고, 0초에 n 발 이런식으로
	// utilty로 따로 빼서 하겠다.
	enum class FireMode
	{
		None = -1,
		OneShot,
		Repeat
	};
	// 커스텀 타입 등록
	TYPE_DECLARATIONS(Player, Actor)

public:
	Player();;

private:
	// 이벤트 함수 오버라이드.
	virtual void Tick(float deltaTime) override;

	// 이동 처리 함수.
	void Move(float direction, float deltaTime);

	// 탄약 발사 함수
	void Fire();

	// 연속 발사 함수
	void FireInterval();

	// 발사 가능 여부 확인 함수
	inline bool  CanShoot() const { return timer.IsTimeOut(); }  // 연사를 눌렀을 때 충분한 시간이 흘러야 가능하다는 걸 표현

	private:
		// 이동처리에 필요한 변수
		float xPosition = 0.0f;

		// 이동속도 변수
		float moveSpeed = 70.0f;
		
		// 연사 처리 위해 아래 3개 추가
		// 발사 모드 변수
		FireMode fireMode = FireMode::None;

		// 타이머 변수
		Timer timer;

		// 연사 시  발사 간격(단위 : 초)
		float fireInterval = 0.2f;


};

