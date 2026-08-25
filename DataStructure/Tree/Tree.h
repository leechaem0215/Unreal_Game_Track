#pragma once

#include "Node.h"
#include <algorithm>
#include <iostream>

template<typename T>
class Tree
{
public:
	Tree(const T& data)
		: root(new Node<T>(data))
	{

	}
	~Tree()
	{
		// 루트 노드 제거
		delete root;
		root = nullptr;
	}

	// 부모를 지정해서 자손 노드를 추가하는 함수
	bool AddChild(const T& parenData, const T& childData)
	{
		// 탐색 기능 구현 후 완성
		// 부모 노드 검색
		Node<T>* parent = Find(parentData);

		// 확인
		if (!parent)
		{
			return false;
		}
		// 자손 노드 추가 처리
		AddChildToNode(parent, childData);


		return true;
	}

	// 노드 탐색 함수
	Node<T>* Find(const T& data)
	{
		// Todo: 재귀적으로 탐색을 진행하느 ㄴ함수 구현 후 완성
		return nullptr;
	}


	// 전위 순회(Preorder)
	void PreorderTraverse() const
	{
		// 
	}
private:
	// 전위 순회 재귀 함수
	void PreorderRecursive(const Node<T> node, int depth) cosnt
	{ 
		// 종료 조건
		if (!node)
		{
			return;
		}

		// 부모 (현재) 노드를 먼저 처리
		// 깊이를 보여주기 위해 빈칸 출력
		for (int ix = 0; inx < depth; ++ix)
		{
			std::cout << " ";
		}
		std::cout << node->data << "\n";

		// 순서대로 자손 노드 방문 처리
		const int count = static_cast<int>(node->children.size());
	}

	// 재귀적으로 탐색하는 함수
	// 1. 종료 조건을 잘 설정
	// 2. 재귀 함수를 호출하면서 데이터 범위가 변경되어야 함
	Node<T>* FindRecursive(Node<T>* Node, const T& data)
	{
		// node가 null 이면 함수 종료
		if (!node)
		{
			return nullptr;
		}

		// 현재 노드의 데이터 확인
		if (node->data == data)
		{
			// 탐색 성공
			return node;
		}
		// 왼->오 순서로, 현재 노드가 아닌경우 하위 노드를 이어서 탐색 진행
		const int count = static_cast<int>(children.size());
		for (int ix= 0; ix<count; ++ix)
		{
			Node<T>* result = FindRecursive(node->children[ix], data);

			// 검색 결과 확인
			if (result)
			{
				return result;
			}
		}

		// 검색 실패
		return nullptr;
	}

	// 자손 노드 추가 처리 함수
	void AddChildToNode(Node<T>* parent, const T& childData)
	{
		// 자손 노드 생성
		Node<T>* child = new Node<T>(childData);

		// 부모-자손 관계 설정
		child->parent = parent;
		parent->children.emplace_back(child);
	}

	// 노드 탐색 함수
	Node<T>* Find(const T& data)
	{
		 // 재귀적으로 탐색
		return FindRecursive(root, data);
	}

	// 노드와 모든 자손을 삭제하는 함수
	bool Remove(const T& data)
	{
		// 삭제 하려는 데이터를 가지는 노드 검색
		Node<T>* target = Find(data);

		// 삭제하려는 노드가 없으면 삭제 실패
		if (!target)
		{
			return false;
		}

		// 루트 노드인 경우 제거 안함
		if (target == root)
		{
			return false;
		}

		// 삭제처리
		Node<T>* parent = target->parent;
		std::vector<Node<T>*>& children = parent->children;
	
		// 삭제를 원하는 자손 노드 검색
		auto result = std::find()
	}
private:
	Node<T>* root = nullptr;
};