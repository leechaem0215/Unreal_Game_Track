#include <iostream>

// 전방 선언하는 이유

// 선언 적어주기.
// void Log(const char*);
// 링커에서 파일 하나하나 다 검수함.
// 연결해야하는지 하지 않아야하는지.

// 만약 Log.cpp를 삭제했다면 링크단에서 오류발생, 컴파일은 정상
// 컴파일은 선언 있고, 동작할 코드는 어딘가에 있겠지 하고 링크한테 넘김. 구문만 봄
// LNK 오류? 링크단 오류


// 이런식으로 보통 사용함.
// 헤더파일의 목적 : 선언하는것
#include "Log.h"

int main()
{
	//std::cout << "Hello\n";
	Log("Hello");


}
//#include "EndBrace.h"