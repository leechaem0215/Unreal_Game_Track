#pragma once

// 전방선언
template<typename T>
class BinaryTree;

template<typename T>
class Node
{
	// friend 선언
	friend class BinaryTree<T>;

public:
	// getter 추가
	const T& GetData() const { return data; }
	Node<T>* GetParent() const { return parent; }
	Node<T>* GetLeftParent() const { return left; }
	Node<T>* GetRightParent() const { return right; }

private:
	// 생성자 / 소멸자
	Node(const T& data)
		:data(data)
	{
	}

	~Node()
	{
		// 두 자식 노드를 모두 제거
		delete left;
		left = nullptr;

		delete right;
		right = nullptr;
	}

	// 복사 방지
	Node(const Node& other) = delete;
	Node& operator=(const Node& other) = delete;

private:
	// 데이터 필드
	T data;

	// 부모참조 변수
	Node<T>* parent = nullptr;

	// 자식 노드 참조 변수
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};
