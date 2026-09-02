#pragma once

#include "Bounds.h"
#include <vector>

// 영역에 포함될 노드 데이터를 가지고있어야함.

// 메모리 삭제함수
template<typename T>
void SafeDelete(T*& t)
{
	if (t) {
		delete t;
		t = nullptr;
	}
}

// 쿼드 트리 노드
class Node
{
	// 영역 구분을 위한 열거형을 강타입으로
	enum class NodeIndex
	{
		// 경계선에 걸치지 않고 완전 포함
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,

		Straddling, // 경계선에 걸치는 경우
		OutOfArea // 영역 벗어난 경우
	};
public:
	Node(const Bounds& bounds, int depth = 0);
	~Node(); // 상속아니라 virtual 안붙임

	// 노드 삽입할 때 사용할 함수
	bool Insert(Node* node);

	// 검색 영역과 실제로 겹치는 노드 목록을 반환하는 함수
	void Query(const Bounds& queryBounds, std::vector<Node*>& results) const;

	// 정리
	void Clear();

	// Getter
	const Bounds& GetBounds() const { return bounds; }
	const std::vector<Node*>& Points() const { return points; }

	Node* TopLeft() const { return topLeft; }
	Node* TopRight() const { return topRight; }
	Node* BottomLeft() const { return bottomLeft; }
	Node* BottomRight() const { return bottomRight; }


private:
	// 영역을 4분할 할 때 사용할 함수
	// 최대 깊이에 도달해서 분할에 실패하면 false 반환
	bool Subdivide();

	// 분할되었는지 여부 확인 함수
	bool IsDivided() const;

	// 전달한 영역과 겹치는 영역을 반환하는 함수
	NodeIndex TestRegion(const Bounds& targetBounds) const; // 특정영역 확인

	// 전달한 영역이 포함되거나 걸치는 영역을 모두 구할 때 사용할 함수
	std::vector<NodeIndex> GetQuads(const Bounds& targetBounds) const;
	
	// 자식노드 정리 함수
	void ClearChildren();

private:
	// 현재 노드의 깊이
	int depth = 0;

	// 현재 노드의 영역
	Bounds bounds;

	// 현재 영역에 포함된 노드
	std::vector<Node*> points;

	// 자식노드
	Node* topLeft = nullptr;
	Node* topRight = nullptr;
	Node* bottomLeft = nullptr;
	Node* bottomRight = nullptr;
};

