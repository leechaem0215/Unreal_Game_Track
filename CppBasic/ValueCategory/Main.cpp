#include <iostream>
#include <string>

class Actor
{
public:
	Actor(std::string& newName)
		: name(newName)
	{

	}
private:
	std::string name;
};

int main()
{
	std::string actor2Name = "TestActor";
	Actor actor1("Test");
	Actor actor2(actor2Name);

	int count = 10;

	// L-Value Reference (L-Value 참조)
	int& lRef = count;
	// int& lRef2 = 10; // 오류

	// R-Value Reference(R-Value 참조)
	// int&& rRef = count; // R 참조는 L이 올 수 없다
	int&& rRef = 10;
}