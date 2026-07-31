#pragma once // 인클루드 가드
class Point
{
public:
	Point(int x = 0, int y = 0);
	
	// 덧셈 연산자 오버로딩. // 덧셈 결과 반환값있음
	Point operator+(const Point& other) const; // 받는 항목 변경 안하려고 const 상수화

	// 값 출력 함수
	void  Print();
private:
	int x = 0;
	int y = 0;
};

