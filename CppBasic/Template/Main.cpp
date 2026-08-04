#include <iostream>

template<typename T>
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// 클래스 템플릿
template<typename T, int size =10>
class Data
{
public:
	Data(const T& newData)
		:data(newData)
	{

	}
	T GetData() const { return data; }
	void SetData(const T& newData) { data = newData; }
	int GetSize() const { return size; }
private:
	T data = {};
};

int main()
{
	int a = 10;
	int b = 30;

	swap(a, b);
	std::swap(a, b);

	Data<int> intData(30);
	std::cout << intData.GetData() << "\n";
	std::cout << "Size: " << intData.GetSize()
		<< ", Data: " << intData.GetData()
		<< "\n";

	Data<float> pi(3.141592f);
	std::cout << pi.GetData() << "\n";
	std::cout << pi.GetSize() << "\n";

	std::cin.get();
}