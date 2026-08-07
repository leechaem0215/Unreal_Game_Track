#include <iostream>
#include <string>

class Actor
{
public:
	/*Actor(std::string& newName)
		: name(newName)
	{

	}*/
	Actor(const char* newName)
	{
		// 이름 값 설정
		// 1. 공간 할당
		size_t length = strlen(newName) + 1;
		name = new char[length] {};

		// 2. 값 복사
		strcpy_s(name, length, newName);
	}
	~Actor()
	{
		if (name)
		{
			delete[] name;
			name = nullptr;
		}
	}

	// 복사 생성자 - copy constructor
	Actor(const Actor& other)
	{
		// 0. 기존 공간 해제
		if (name)
		{
			delete[] name;
			name = nullptr;
		}
		// 1. 공간 할당
		size_t length = strlen(other.name) + 1;
		name = new char[length] {};

		// 2. 값 복사
		strcpy_s(name, length, other.name);
	}

	// 이동 생성자 - move constructor
	Actor(Actor&& other) // R-Value
		//: name(other.name)
	{
		// 기존 메모리 해제
		if (name)
		{
			delete[] name;
			name = nullptr;
		}
		// 주소 값 이전
		name = other.name;

		// 주소값을 이전시킨 후에 원본 주소를 null 대입
		other.name = nullptr;
	}
private:
	//std::string name;
	char* name = nullptr;
};

int main()
{
	std::string actor2Name = "TestActor";
	// Actor actor1("Test"); // 이거 되게하려면 Actor()의 파라미터를 const 붙여주면 된다.
	Actor actor2(actor2Name);

	int count = 10;

	// L-Value Reference (L-Value 참조)
	int& lRef = count;
	// int& lRef2 = 10; // 오류

	// R-Value Reference(R-Value 참조)
	// int&& rRef = count; // R 참조는 L이 올 수 없다
	int&& rRef = 10;
}