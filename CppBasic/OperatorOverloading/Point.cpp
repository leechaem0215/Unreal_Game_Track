#include "Point.h"
#include <iostream>

Point::Point(int x, int y)
	: x(x), y(y) // 초기화, 멤버이니셜라이저
{
	// 복잡한 초기화 작업 or 동적 할당 및 여러 줄의 초기화가 필요할 때
	x = x;
	y = y;
}

Point Point::operator+(const Point& other) const
{
	// 멤버함수 고치지 않게 함 뒤에 const 붙여서 (x, y 가 멤버함수)
	return Point(x + other.x, y + other.y);
}

void Point::Print()
{
	std::cout << "(" << x << ", " << y << ")\n";
}
