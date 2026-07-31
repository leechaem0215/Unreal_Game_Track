#include <iostream>
#include <Windows.h>
#include <string>

class Player {
public:
	// 생성자
	Player(const char* name) {
		// 문자열 저장을 위해 동적할당.
		size_t length = strlen(name + 1);
		this->name = new char[strlen(name) + 1]; // 왜 한칸 더할까? \0 문자 하나 넣어주기.
		
		// 문자열 값 복사
		strcpy_s(this->name, length, name); // 멤버 변수에 복사가 됌


		// 값 저장.
		for (size_t ix = 0; ix < length - 1; ++ix) {
			this->name[ix] = name[ix];
		}

		this->name[length - 1] = '\0';
	}
	// 소멸자 // 동적할당 했기 때문에
	~Player() {
		// name 이 null 인지 확인
		// if (name) // true, false 로 판단, 0이 아닌 모든 값은 true임
		// if(name = nullptr)
		if (nullptr != name){
			delete[] name;
		}
	}
	void PrintName() const {
		// 함수 자체를 고정하고 싶을때 const 함. 다른 걸 못 가릴킬 때
		std::cout << name << "\n";
	}
private:
	// 이름을 저장할 변수
	char* name = nullptr;
};

int main() {
	// 문자열
	auto name = "Ronnie"; // const char* // 배열 7개짜리, 문자열 종료 알리기 위해 +1 (\0 : 문자열 종료 문자)
	char namaeArray[4];

	size_t length = strlen(name);

	// Wide Character
	const wchar_t* wcName = L"RonnieJ"; // Wide는 L을 꼭 붙여야한다.
	// std::wstring

	// Windows 타입
	//WCHAR; // windows에 WCHAR 라는 타입이 있다.

	// STL 문자열 타입
	std::string nameString = "Ronnie Jang";
	std::cout << nameString << "\n";
	std::cout << "nameString Length: " << nameString.size() << "\n"; // 문자열 사이즈

	// std::string 을 C-Raw string 으로
	const char* rawName = nameString.c_str(); // const char* 형태로 꺼내는 코드


	std::cout << "string length: " << length << "\n";
	std::cin.get();
}