#pragma once

#include <random>

namespace Util
{
	// 랜덤 엔진 반환함수
	inline std::mt19937& GetRandomEngine()
	{
		// 프로그램 실행 중 1번만 생성되는 랜덤 엔진
		static std::mt19937 engine; // 프로그램 종료되기 전까지 제어되지 않음
		return engine;
	}

	// 랜덤 시드 설정 함수
	// 시간을 기반으로 설정하는 경우가 많음
	inline void SetRandomSeed()
	{
		// 하드웨어 기반 난수 생성기(시드값 제공)
		std::random_device randomDevice;

		// 랜덤 엔진에 종자값 (시드) 설정
		GetRandomEngine().seed(randomDevice());
	}
	// 정수기반 난수 함수
	inline int RandomRange(int min, int max)
	{
		// min에서 max 까지 균등하게 부동소수점 난수를 생성해주는 분포정의
		std::uniform_real_distribution<int> distribution(min, max); // real 은 실수

		// 난수 반환
		return distribution(GetRandomEngine()); // GetRandomEngine 엔진 만든거 넣어줌
	}


	// 부동 소수점 난수 함수
	inline float RandomRange(float min, float max)
	{
		// min에서 max 까지 균등하게 부동소수점 난수를 생성해주는 분포정의
		std::uniform_real_distribution<float> distribution(min, max); // real 은 실수

		// 난수 반환
		return distribution(GetRandomEngine()); // GetRandomEngine 엔진 만든거 넣어줌
	}
}