#include <iostream>

int main() {
	// 입력.
	// 숫자 입력 요청 -> 숫자가 아니면 다시 요청 (예외처리).
	int value = 0;

	// 무한 루프 작성 방법.
	// 1. 종료 조건을 확인.

	while (true) {
		// 기본적으로 문자를 받아야함.
		// 검증용 문자 버퍼
		char buffer[50] = {};
		// char는 사실 숫자 타입이다. 1바이트, 출력할 때 인코딩을 해서 문자로 바꿔주는것.
		// {} 0으로 초기화 해주는 예약어, 버퍼를 넣는다.
		std::cout << "0이 아닌 숫자를 입력하세요(첫 번쨰) : ";
		std::cin >> buffer;

		// 검증
		// int -> 32bit? no 
		// 재정의해서 int 많이 사용한다. 32로 재정의 함. ms 에서는 int가 32비트임.
		// 왜 그렇지 하는지? 알아두기
		// long long 은 64로 사용
		// __int64
		if ((value = atoi(buffer)) == 0) // atoi가 0이 반환됨
		{
			// 0이 아니면 유효
			std::cout << "숫자를 입력하세요\n";
		}
		// 숫자 입력이 제대로 된 경우.
		else
		{
			// 루프 종료
			break;
		}
	}

	int value2 = 0;
	std::cout << "숫자를 입력하세요(두 번째): ";
	std::cin >> value2;

	std::cout
		<< "입력한 두 수의 합은 "
		<< (value + value2)
		<< "입니다. \n";

	//std::cout << "입력하신 숫자는 " << value << "입니다.\n";

	std::cin.get();
}