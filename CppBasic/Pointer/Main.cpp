#include <iostream>

// 참조를 한다는 것은 주소를 복사 또는 사용한다는 의미
void Release(int** t) // 포인터 받음 (int*& t) : 포인터의 레퍼런스?
{
	if (*t != nullptr)
	{
		delete *t;
		*t = nullptr;
	}
}

int main()
{
	int var = 8;
	int* ptr = &var; // 포인터가 가리키는 공간이 int
	// 포인터에 값 넣으면 안됌

	int* testPtr = new int;
	Release(&testPtr);
	//delete testPtr;
	//testPtr = nullptr;

	////////////////////////////////
	
	// 동적 할당.
	const int length = 100;
	int* buffer = new int[length];
	int** bufferPtr = &buffer; // 포인터가 가리키는 공간이 int 타입의 포인터
	// 포인터가 한번이면 주소 한번 타면 되는데 더블은 두번 타야 주소나온다.
	// new를 했으면 delete를 해주어야함.
	// *buffer = 0;
	memset(buffer, 0, sizeof(int) * length); // 공간 초기화, 초기화 하지 않으면 아무런 값 들어감.

	delete[] buffer; // 배열삭제로

	std::cin.get();
}
/*
int 타입으로 포인터 잡아서 B
new int 할당 했는데 둘이 메모리 적재되는 공간이 다름

왼쪽은 stack, 오른쪽은 Heap
왼쪽 포인터, 오른쪽은 Heap
*/