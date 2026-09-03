#pragma once

#include "Node.h"
#include <vector>
#include <queue>
#include <unordered_map>

class AStar
{
private:
	struct Direction
	{
		Direction()
		{
		}

		Direction(int x, int y, float cost)
			: x(x), y(y), cost(cost)
		{
		}

		// 상하좌우 이동 비율은 1, 대각선은 삼각형을 유지하여 루트2, 수치로 구하면 1.4142... 
		int x = 0;
		int y = 0;
		float cost = 0.0f;
	};

	// fCost 비교
	struct CompareNode
	{
		bool operator()(const Node* left, const Node* right) const {
			if (left->fCost == right->fCost) {
				return left->gCost < right->gCost;
			}

			return left->fCost > right->fCost;
		}
	};

	// 맵에 대한 정보 열거형으로
	// 그리드 타일의 종류(열거형)
	// char 타입 -> 문자타입 -> 숫자를 문자화해서 사용하는 것뿐임. // 1바이트 크기를 할당하고 싶을 때 많이 사용
	enum class TileType { // 최근에는 강타입 열거형을 사용함
		Ground = 0,
		Wall = 1,
		Start = 2,
		Goal = 3,
		Visited = 5, // 맵의 방문 지점
	};

public:
	AStar();
	~AStar();

	// 메시지 (객체 지향 프로그래밍 용어) - 공개 메소드 (인터페이스)


	// 경로 탐색 요청 함수
	std::vector<Position>FindPath(
		const Position& startPosition,
		const Position& goalPosition,
		std::vector<std::vector<int>>& grid);

	void DisplayGridWithPath(
		std::vector<std::vector<int>>& grid,
		const std::vector<Position>& path);

private:
	// 메소드 (클래스(또는 구조체))

	// 이전에 탐색에 사용한 정보 및 노드를 정리하는 함수
	void Clear();

	// 노드 생성 전문 함수
	Node* CreateNode(const Position& position, Node* parent = nullptr);

	// 부모 노드를 역추적해서 경로를 구성하는 함수
	std::vector<Position> ConstructPath(Node* destination);

	// 휴리스틱(추정비용) 계산 함수)
	float CalculateHeuristic(const Position& current, const Position& goal) const;

	// 유효한 맵인지 검증
	// 그리드 검증 함수
	bool IsValidGrid(const std::vector<std::vector<int>>& grid) const;

	// 이동하려는 좌표가 유효한지 확인
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid) const;

	// 옵션 : 대각선 이동이 장애물 모서리를 통과하는지 확인
	bool IsDiagonalBlocked(
		const Position& current,
		const Direction& direction,
		const std::vector<std::vector<int>>& grid
	) const; // 장애물을 통과했는지, 아무것도 없는 대각선을 통과한건지

	// open 목록 및 Closed 목록 검사 함수
	Node* FindOpenNode(const Position& position) const;
	bool IsInClosedList(int x, int y) const;

	// 목적지 인지 확인하는 함수
	bool IsDestination(const Node* node) const;

	// 탐색한 정보를 화면에 그려주는  함수
	// 이전 탐색 표시를 지우고 그리드는 출력하는 함수
	void ClearVisualization(std::vector<std::vector<int>>& grid) const;
	void DisplayGrid(std::vector<std::vector<int>>& grid) const;

	// 최적화하기 위한 추가 함수
	std::vector<Node*> getNeighbors(Node* node, const std::vector<std::vector<int>>& grid);

	int NodeMapKey(const Position& position) const;

private:
	// 동적 할당된 모든 노드를 소유하는 목록
	// 메모리 관리를 위해 사용
	std::vector<Node*> allocatedNodes;
	int width = 0;

	// 탐색할 노드/탐색을 마친 노드 목록
	std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
	std::vector<Node*> closedList;
	std::unordered_map<int, Node*> nodeMap;

	Node* startNode = nullptr;
	Node* goalNode = nullptr;

};