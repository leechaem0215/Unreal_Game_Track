#include <iostream>
#include "Point.h"

int main()
{
	// 포인터 객체 간의 덧셈 연산
	Point p1(1, 1);
	Point p2(2, 2);

	Point p3 = p1 + p2;

	p3.Print();
}