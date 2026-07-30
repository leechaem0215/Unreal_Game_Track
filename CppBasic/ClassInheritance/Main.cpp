#include <iostream>

class Base
{
public:
	Base() {
		std::cout << "Base() called\n";
	}
	~Base() {
		std::cout << "~Base() called\n";
	}

	void Play() {
	
	}
};

class Derived : public Base 
{
public:
	Derived() {
		std::cout << "Derivce() called\n";
	}
	~Derived() {
		std::cout << "~Derivce() called\n";
	}
	void Attack() {
	
	}
};

int main() {
	Base* b = new Derived();
	b->Play();
	// b->Ataack(); // 이건 불가

	delete b;
	b = nullptr;
}

// 생성할 때 부모 계층 먼저 처리 후 자식 계층 처리
// 소멸될 때는 자식계층 먼저 처리