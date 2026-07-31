#pragma once
#include <iostream>

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