#pragma once

# include <iostream>
// 사각영역
class Bounds
{
public:
	Bounds(int x, int y, int width = 1, int height = 1)
		: x(x), y(y), width(width), height(height)
	{
	}

	// Getter
	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	// 오른쪽 및 아래쪽 경계 Getter
	int GetXMax() const { return x + width; }
	int GetYMax() const { return y + height; }

	// Setter

	// 점이 Bounds 안에 있는지 확인
	bool Contains(int pointX, int pointY) const // 값 비교만 할거라 const 붙임
	{
		return pointX >= x && pointX < GetXMax() && pointY >= y && pointY < GetYMax();
	}

	// 다른 사각형이 현재 영역에 포함되는지 확인
	bool Contains(const Bounds& other) const
	{
		return other.x >= x && other.GetXMax() < GetXMax() && other.y >= y && other.GetYMax() < GetYMax();
	}

	// 다른 사각형과 겹치는지 확인
	bool Intersects(const Bounds& other) const // 완전 포함이 아니어도 ㄱㅊ
	{
		return other.x < GetXMax() && other.GetXMax() > x && other.y < GetYMax() && other.GetYMax() > y;
	}

	// 연산자 오버로딩
	friend std::ostream& operator<<(std::ostream& os, const Bounds& bounds) {
		os << "(" << bounds.x << ", " << bounds.y << ")" << " Width: " << bounds.width << " Height: " << bounds.height << "\n";
		return os;
	}

private:
	// 위치 (콘솔 좌표계 기준)
	int x = 0;
	int y = 0;


	// 크기
	int width = 1;
	int height = 1;

};

