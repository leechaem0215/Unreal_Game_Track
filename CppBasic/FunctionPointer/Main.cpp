#include <iostream>

void main()
{
	// 함수 포인터
	void(*FunctionPointer) {};

	// 함수 포인터에 함수 주소 저장
	FunctionPointer = Test;
	
	FunctionPointer();
	Test();
}