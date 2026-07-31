#include <iostream>

void Increment() 
{
	static int count = 0;
	++count;
	std::cout << "Count: " << count << "\n";
}

int personCount = 0;

class Person
{
public:
	Person()
	{
		++personCount;
		std::cout << personCount << "번째 Person 객체 생성\n";
	}
	~Person()
	{
		--personCount;
	}
};

int mani() 
{
	Person p1;
	Person p2;
}