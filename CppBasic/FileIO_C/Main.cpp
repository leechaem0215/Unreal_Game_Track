#include <iostream>
#include <cstdio>

int main() 
{
	// 파일 입출력을 위한 변수
	FILE* file = nullptr;

	// 파일 열기
	auto result = fopen_s(&file, "Test.txt", "rb"); // wb: 쓰기모드로 열면 내용 없어짐

	if (!file)
	{
		std::cout << "파일 열기 실패\n";
		return 1;
	}

	// 파일 열기 성공
	std::cout << "파일 열기 성공\n";

	// 파일 닫기
	fclose(file);
	file = nullptr;
}