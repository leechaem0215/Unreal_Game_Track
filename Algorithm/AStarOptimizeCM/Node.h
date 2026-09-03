#pragma once

class Position
{
public:
	Position(int x = 0, int y = 0)
		: x(x), y(y)
	{

	}

	// 동등 비교 연산자 오버로딩
	bool operator==(const Position& other) const
	{
		return x == other.x && y == other.y;
	}

public:
	// 가로 세로 위치
	int x = 0;
	int y = 0;
};

// A* 탐색에 사용되는 노드 클래스
class Node
{
public:
	Node(const Position& position, int idx, Node* parent = nullptr)
		:position(position), idx(idx), parent(parent)
	{

	}

	bool operator()(const Node* a, const Node* b) const {
		return a->fCost > b->fCost;
	}

public:
	// 노드의 위치 정보
	Position position;

	int idx = -1;
	bool visited = false;

	// 노드의 비용 정보
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;

	// 최종 경로를 역추적할 때 사용할 부모 노드
	Node* parent = nullptr;
};
