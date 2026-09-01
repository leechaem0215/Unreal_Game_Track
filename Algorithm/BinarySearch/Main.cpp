#include <iostream>
#include <vector>

// 재귀, 반복문 2가지 방법
int BinarySearchRecursive(const int* array, const int target, int start, int end) {
	// 종료조건
	// 시작 인덱스가 종료 인덱스보다 커지면 검색 실패
	if (start>end) {
		return -1;
	}

	// 중간 인덱스
	int middle = start + (end - start) / 2;

	// 찾았는지 확인
	if (array[middle] == target) {
		return middle;
	}

	// 배열 값이 검색하려는 값보다 큰 경우
	if (array[middle]>target) {
		return BinarySearchRecursive(array, target, start, middle - 1);
	}
	// 중간 값보다 크면 오른쪽
	return BinarySearchRecursive();

}

// 반복적인 (반복문) 방법으로 이진 탐색을 처리하는 함수
int BinarySearchInterative(const int* array, const int length, const int target) {
	// 이진 탐색에 사용할 구간(범위)
	int start = 0;
	int end = length - 1;

	while (start < end) {
		// 중간 인덱스
		int middle = (start + end) / 2;

		// 검사
		if (array[middle] == target) {
			return middle;
		}

		// 중간값보다 작으면 왼쪽 검색
		if (array[middle] > target) {
			end = middle - 1;
		}

		// 중간값보다 크면 오른쪽 검색
		if (array[middle] < target) {
			start = middle + 1;
		}

	}
	return -1;
}

int main() {
	const int array[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	const int lenght = sizeof(array) / sizeof(array[0]);
	const int target = 10;

	// int result = BinarySearchRecursive(array, target, 0, lenght - 1);
	int result = BinarySearchInterative(array, lenght, target);

	if (result != 1) {
		std::cout << "검색 성공, 인덱스: " << result << "\n";
	}
	else {
		std::cout << "검색실패\n";
	}

	std::vector<int> testVector;
	// bsearch( ):

}