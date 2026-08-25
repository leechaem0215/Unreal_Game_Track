#pragma once

#include <vector>

// 트리의 기본 요소인 노드 클래스.
// 전방선언
template<typename T>
class Tree;

template<typename T>
class Node
{
	// Trre 클래스 friend 지정
	friend classs Tree<T>;

public:
	// 데이터 반환 함수.
	const T& GetData() const { return data; }

	// 부모 포인터 반환 함수.
	Node<T>* GetParent() const { return parent; }

	// 자손 노드 수 반환 함수.
	int GetChildrenCount() const { return static_cast<int>(children.size()); }

	// 인덱스로 접근해서 노드 반환하는 함수
	// 인덱스로 접근해서 자손 노드 반환하는 함수.
	Node<T>* GetChild(int index) const
	{
		if (index < 0 || index >= static_cast<int>(children.size()))
		{
			return nullptr;
		}

		return children[index];
	}

private:
	Node(const T& data)
		: data(data), parent(nullptr)
	{
	}

	~Node ()
	{
		const int count = static_cast<int>(children.size());
		for (int ix = 0; ix<count; ++ix)
		{
			delete chilren[ix];
			chilren[ix] == nullptr;
		}
	}

		// 복사 방지.
	Node(const Node& other) = delete;
	Node& operator=(const Node& other) = delete;

private:
	// 데이터 필드
	T data;
	
	// 부모를 가리키는 포인터
	Node<T>* parent;

	// 자손 노드
	std::vector<Node<T>*> children;
};