#include "HashTable.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HashTable table;

	// 키-값 데이터 추가
	table.Add("Ronnie", "010-1234-1234");

	// 중복 키 추가 확인
	if (!table.Add("Ronnie", "010-1234-5678"))
	{
		std::cout << "이미 같은 키가 저장되어 있음.\n";
	}

	table.Add("Ronnie2", "010-1234-1232");
	table.Add("Ronnie3", "010-1234-1233");
	table.Add("Ronnie4", "010-1234-1235");

	// 출력
	std::cout << "\n전체 데이터\n";
	table.Print();


	// 검색
	std::string number;
	if (table.Find("Ronnie", number))
	{
		std::cout << "\n 검색 결과: Ronnie, " << number << "\n";
	}

	// 삭제
	if (table.Delete("Ronnie"))
	{
		std::cout << "Baker 항목 삭제\n";
	}

	// 출력
	std::cout << "\n삭제 후 데이터\n";
	table.Print();
}