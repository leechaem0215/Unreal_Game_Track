#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// 배열 전달받아서 원소를 출력하는 함수
void PrintArray(int* array, int count) {
	// array 의 사이즈를 못 구함. 원시배열은 넘어오면서 포인터로 바뀜
	// 그래서 count 로 따로 넣어야함. = 원소의 개수
	
	// 배열 원소의 수
	for (int ix = 0; ix < count; ++ix) {
		std::cout << array[ix] << " ";
	}
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//std::array<int, 5> stdArray2; // 함수로 넘어가도 크기알 수 있음
	// 좋지만 불편, 그걸 보완한게 벡터, 동적배열
	 
	
	// 배열
	const int length = 5; // 상수로 하는게 좀 더 좋은 방법
	int array[length];
	memset(array, 0, sizeof(int) * length); // &array[0] 와 같은 첫번째 인자
	
	// 동적 배열.
	int* dArray = new int[length];
	// 스택은 몇 메가

	// 메모리 해제
	delete[] dArray;


	// 배열을 포인터로 다루기.
	int* ptr = array;
	*(ptr + 2) = 30; // 포인터의 덧셈은 메모리 점프. // 타입으로 지정한 크기만큼

	// 배열 순회
	for (int ix = 0; ix < length; ++ix) {
		array[ix] = ix +1;
	}

	// Range-Based Loop (범위 기반 루프)
	// C# 의 foreach 와 같은 동작 원리
	for (const int value : array) { // 원시배열을 함수로 넘길때
		std::cout << value << " ";
	}

	PrintArray(array, length);

	std::cout << "\n";
	std::cin.get();
}