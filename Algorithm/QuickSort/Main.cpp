#include <iostream>
#include <cstdlib>
#include <ctime>

// 비교를 위한 함수 포인터
typedef bool (*Comparer)(int, int);

bool LessEqual(int a, int b) { return a <= b; }
bool GreaterEqual(int a, int b) { return a >= b; }

// min과 max 사이의 랜덤 정수를 반환하는 함수
int RandomRange(int min, int max) {
	// min max 사이의 거리
	int diff = (max - min) + 1;
	return ((diff * rand()) / (RAND_MAX + 1)) + min;
}

void PrintArray(const int* array, int length) {
	for (int ix = 0; ix < length; ++ix) {
		std::cout << array[ix];

		if (ix < length - 1) {
			std::cout << ", ";
		}
	}
}

// 피벗 선택 함수
int Partition(int* array, int left, int right, Comparer comparer = GreaterEqual) {
	// 피벗을 선택하는 방법은 다양한데 간단하게 첫번째 요소를 선택
	int pivot = array[left];
	int low = left + 1; // 왼 -> 오 이동하면서 피벗보다 큰 값 찾음

	int high = right; // 오 -> 왼 이동하면서 피벗보다 작은 값 찾는데 사용
	
	// low와 high 인덱스가 교차할 때까지 진행
	while (low <= high&&array[low]<=pivot) {
		// 왼->오 이동하면서 값 찾기
		++low;
	}
	while (high > left &&  pivot <= array[high]) {
		// 왼->오 이동하면서 값 찾기
		--high;
	}

	if (low > high) {
		break;
	}

	std::swap<int>(array[low], array[high]);

	// 피벗을 최종 위치로 이동처리
	// array[left] 값이 피벗 값(첫번째요소)
	std::swap<int>(array[left], array[high]);
}

int main() {
	// 랜덤 시드 전달
	srand(static_cast<uint32_t>(time(nullptr)));

	const int length = 100;

	int original[length] = {};
	for (int ix = 0; ix < length; ++ix) {
		int value = RandomRange(1, length);
		original[ix] = value;
	}
	int array[length] = {};

	// 메모리 복사
	memcpy(array, original, sizeof(int) * length);
}