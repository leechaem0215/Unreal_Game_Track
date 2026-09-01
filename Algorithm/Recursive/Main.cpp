#include <iostream>

// 거듭 제곱 재귀 함수
int Power(int x, int y)
{
	// 종료 조건
	if (y==0) {
		return 1;
	}
	return x * Power(x , y - 1);
}

// 1부터 지정한 수까지의 합을 구하는 재귀함수
int Sum(int number)
{
	// 종료조건
	if (number == 1)
	{
		return 1;
	}
	return number + Sum(number - 1);
}

int main()
{
	// 2의 8승 = 256
	int power = Power(2, 8);

	const int target = 5;
	int result = Sum(target);

	std::cout << "결과: " << result << "\n";
	std::cout << "결과: " << power << "\n";
}