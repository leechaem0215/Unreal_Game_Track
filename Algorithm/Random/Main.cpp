#include <iostream>
#include <cstdlib>
#include <ctime>

// 정수, 범위를 지정해서 특정 범위의 정수 난사를 반환하는 함수
int RandomRange(int min, int max) {
	//const int diff = (max - min) + 1;
	//return (rand() % diff) + min;

	//
	const int diff = (max - min) + 1;
	return ((rand() * diff) / (RAND_MAX + 1)) + min;
}

// 부동소수 난수 생성합수
float RandomRange(float min, float max){
	// 0-1 사이의 부동소수 난수 구하기
	float percent = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	// 전달 받은 구간으로 변환
	float diff = (max - min);
	return percent * diff + min;
}

int main() {
	// 현재 시간 값을 받음
	// 종자값을 가변적으로 설정해야 함
	// 많은 경우에 시간을 활용
	int64_t seed = time(nullptr);

	// 종자값(seed)
	srand(static_cast<uint32_t>(seed)); // 같으면 안됌 // 시간

	const int count = 5;

	for (int i = 0; i < count; i++) {
		//std::cout << "Random Number: " << rand() << "\n";
		std::cout << "Random Number: " << RandomRange(1.0f, 5.0f) << "\n";
	}
}