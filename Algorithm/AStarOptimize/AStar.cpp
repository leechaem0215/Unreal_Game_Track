#include "AStar.h"
#include <algorithm>
#include <iostream>

#define NOMINMAX
#include <Windows.h>

AStar::AStar()
{
}

AStar::~AStar()
{
    // 초기화
    Clear();
}

// 최적화란?
// 병목을 찾아 적절한 해결방법을 적용
// 안해도 되는 계산을 찾아서 안하게 만드는 것

std::vector<Position> AStar::FindPath(const Position& startPosition, const Position& goalPosition, std::vector<std::vector<int>>& grid)
{
    // 이전에 탐색한 결과 초기화
    Clear();

    // 예외처리
    if (!IsValidGrid(grid)) {
        // 유효하지 않으면 빈 배열 반환
        return {}; // {}; << 이거도 가능 (STL - initialize_list)
    }

    // 시작/목표 위치가 grid 기준에서 문제 없는 위치값인지 확인
    if (!IsInRange(startPosition.x, startPosition.y, grid) || !IsInRange(goalPosition.x, goalPosition.y, grid)) {
        return {};
    }

    // 시작/목표 위치가 이동 불가하면 종료
    if (grid[startPosition.y][startPosition.x] == (int)TileType::Wall || grid[goalPosition.y][goalPosition.x] == (int)TileType::Wall) {
        return {};
    }

    // 이전 탐색 과정의 시각화 제거 (기존에 방문 처리한 값이 있으면 제거)
    ClearVisualization(grid);

    // 탐색시작
    // 시작/목표 노드 생성
    startNode = CreateNode(startPosition);
    goalNode = CreateNode(goalPosition);

    // 시작 노드의 비용 계산 및 openList에 추가해 탐색 시작
    startNode->gCost = 0.0f;
    startNode->hCost = CalculateHeuristic(startPosition, goalPosition); // 추정비용
    startNode->fCost = startNode->gCost + startNode->hCost; // 다익스트라 + 그리드 알고리즘에 해당

    openList.push(startNode);




    // 편의를 위해 사전 비용 설정
    const float diagonalCost = 1.41421f;
    const std::vector<Direction> directions = //Direction 좌표값하고 비용설정할 수 있게 해놓음
    {
        {0, -1, 1.0f}, {0, 1, 1.0f},  // 상 하
        { -1, 0, 1.0f },{1, 0, 1.0f}, // 좌우
        {-1, -1, diagonalCost}, {1, -1, diagonalCost}, // 좌상단, 우상단
        { -1, 1, diagonalCost}, {1, 1, diagonalCost},  // 좌하단, 우하단
    }; // 휴리스틱 계산할 때 현재 위치에서 목표지정할 때 방향이 비용으로 지정이 될 거임, 반대면 비용이 커질 수 있음



    // openList가 빌 때까지 탐색 반복
    while (!openList.empty()) {
        // openList에서 fCost가 가장 작은 노드를 선택
        Node* currentNode = openList.top();
        openList.pop();

        /*for (Node* node : openList) {
            // 더 작은 비용의 노드 검색
            // -> 우선순위 큐를 이용해서 최적화
            if (node->fCost < currentNode->fCost || (node->fCost == currentNode->fCost && node->hCost < currentNode->hCost)) {
                currentNode = node;
            }
        }*/

  
        // 맵이 커지면? 
        // 작은 노드를 빼왔다.
        // 목표 노드인지 확인
        if (IsDestination(currentNode)) {
            // 이동 경로 제작 후 변환
            return ConstructPath(currentNode);
        }

        // 목표 노드가 아니면 방문처리를 해야한다.
        // 현재 노드를 openList에서 제거, 재 방문 방지
        /*auto iterator = std::find(openList.begin(), openList.end(), currentNode);
        // 검색에 성공했는지 확인
        if (iterator != openList.end()) {
            // openaList에서 제거
            openList.erase(iterator);
        }*/

        // 탐색을 마친 노드를 closedList에 추가
        closedList.emplace_back(currentNode);

        // 현재 위치를 기준으로 주변 (8 방향)의 이웃노드를 탐색
        for (const Direction& direction : directions) {
            // 인덱스 문제없으면 비용계산 해서 넣고
            // 현재 노드를 기준으로 인접한 노드의 좌표계산
            // 새로운 좌표(위치) = 현재 위치 + 이동방향
            int newX = currentNode->position.x + direction.x; // 위치 + 벡터 = 위치
            int newY = currentNode->position.y + direction.y;

            // 예외 처리
            if (!IsInRange(newX, newY, grid)) {
                continue;
            }

            // 새로운 위치가 장애물인지 확인
            if (grid[newY][newX] == (int)TileType::Wall) {
                continue;
            }

            // 대각선 이동 시 장애물을 통과하는지 확인
            if (IsDiagonalBlocked(currentNode->position, direction, grid)) {
                continue;
            }

            // 이미 방문한 곳이라면 건너뛰기
            if (IsInClosedList(newX, newY)) {
                continue;
            }

            // 현재 노드를 거쳐서 새로운 위치로 가는데 드는 비용 계산
            float newGCost = currentNode->gCost + direction.cost;

            // 이미 openList에 있는데 비용면에서 더 나은지 확인
            //Node* openNode = FindOpenNode(newX, newY); // 아직 방문은 안했지만 방문하려고 저장한 노드 
            /*if (openNode) {
                // 비용 비교
                if (newGCost < openNode->gCost) {
                    openNode->gCost = newGCost;
                    openNode->fCost = openNode->gCost + openNode->hCost;
                    openNode->parent = currentNode;
                }

                continue;
            }*/

            // 이웃 노드 생성 및 openList에 추가
            Node* neighborNode = CreateNode(Position(newX, newY), currentNode);

            // 새로운 노드의 비용 계산
            neighborNode->gCost = newGCost;
            neighborNode->hCost = CalculateHeuristic(neighborNode->position, goalNode->position);
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

            // 새로운 노드를 openList에 추가
            openList.push(neighborNode);

            // 옵션 : 시각화를 위한 처리
            if (grid[newY][newX] == (int)TileType::Ground) {
                grid[newY][newX] = (int)TileType::Visited;
            }

            // grid 그리기
            DisplayGrid(grid);

            // 스레드 재우기 (애니메이션처럼 단순하게 프레임을 만들기 위해)
            DWORD delay = static_cast<DWORD>(0.5f * 1000);
            Sleep(delay);
        }
    }

    // 빈 경로 반환 (탐색 실패)
    return {};
}

void AStar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Position>& path)
{
    // 그리드랑 경로를 같이 보여주는 함수
    // 기존에 시각화를 위해 사용했던 값 복수
    ClearVisualization(grid);

    // 맵 그리기
    DisplayGrid(grid);

    // 핸들 값 가지고올거임
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    int green = FOREGROUND_GREEN;

    // 이동 경로 그리기
    for (const Position& position : path) {
        // 경로 위치의 타일 값 읽기
        int value = grid[position.y][position.x];

        // 시작/목표 위치는 경로 표시에서 건너뛰기
        if (value == (int)TileType::Start || value == (int)TileType::Goal) {
            continue;
        }

        // 그리기 위해 좌표로 변환한다.
        // 콘솔좌표
        COORD cursorPosition;
        cursorPosition.X = static_cast<short>(position.x * 2);
        cursorPosition.Y = static_cast<short>(position.y);

        // 커서 이동
        SetConsoleCursorPosition(handle, cursorPosition);

        // 텍스트 색 지정
        SetConsoleTextAttribute(handle, green);

        // 글자 출력
        std::cout << "* ";

        // 스레드 재우기
        DWORD delay = static_cast<DWORD>(0.05f * 1000);
        Sleep(delay);
    }
}

void AStar::Clear()
{
    // 탐색 과정에서 생성했던 모든 노드 삭제 및 해제
    for (Node*& node : allocatedNodes) {
        delete node;
        node = nullptr;
    }
    allocatedNodes.clear();
    openList = decltype(openList){};
    closedList.clear();

    startNode = nullptr;
    goalNode = nullptr;
}

Node* AStar::CreateNode(const Position& position, Node* parent)
{
    // 노드를 생성하고, allocatedNodes에 추가
    Node* newNode = new Node(position, parent);
    allocatedNodes.emplace_back(newNode);

    // 생성한 노드 반환
    return newNode;
}

std::vector<Position> AStar::ConstructPath(Node* destination)
{
    // 목표 노드로부터 부모 노드를 따라 경로 역추적
    std::vector<Position> path;
    Node* current = destination;

    while (current) {
        // 현재 노드는 경로 배열에 추가
        path.emplace_back(current->position); // 포지션을 넣어야한다.

        // 부모 노드로 이동해서 경로를 역추적
        current = current->parent;
    }

    // 루프가 종료되면 path 에는 반대 방향의 경로 정보가 저장됨
    // 따라서 다시 역방향으로 뒤집기가 필요
    std::reverse(path.begin(), path.end());

    return path;

}

float AStar::CalculateHeuristic(const Position& current, const Position& goal) const
{
    // 옥타일(8방향) 비용계산 방법
    // 대각선이랑 직선이랑 계산이 다름, 현재 지점에서 목표지점까지 이동하는데 드는 계산이 뭐여
    // 양수값을 구함 그래서 절대값씌움, // 대각선으로 최대한 이동한 다음 직선 값 구함

    // 대각선 이동 허용시 주의 사항 -> 대각선 형태의 장애물을 뚫고 가지 못하게 막아햐 함.
    // 이동하려는 방향성분에 장애물이 있으면 못가게 해야함 (x,y에 장애물 있다면..)


    // 현재 위치에서 목표 지점까지
    // 추정 예상비용 구함
    // 현재 위치와 목표 위치 사이의 차이 계산
    int diffX = std::abs(current.x - goal.x);
    int diffY = std::abs(current.y - goal.y);

    // 대각선 거리와 남은 직선 거리 분리
    int diagonalDistance = std::min(diffX, diffY); // x랑 y중에 더 큰걸 찾음, 대각선으로 2칸이동하면 높이적으로 2칸이동한거랑 같음,. (1,1) (5,3) 일때
    // x로 4칸 y로 2칸은 6칸 이동해야함 직선으로는 // x먼저 이동시키는게 더 좋음 // 대각선으로 얼마나 이동시키는지 // 
    int straightDistance = std::max(diffX, diffY) - diagonalDistance;

    // 대각선 비용
    const float diagonalCost = 1.41421f; // 대각선길이는 루트 2
    const float straightCost = 1.0f;

    return diagonalDistance * diagonalCost + straightDistance * straightCost; // 대각선만큼 이동한 비용하고 직선만큼 이동한 비용
}

bool AStar::IsValidGrid(const std::vector<std::vector<int>>& grid) const
{
    // 그리드가 비어있다면 유효하지 않음
    if (grid.empty()) {
        return false;
    }

    // 행마다 길이가 같은지 확인
    size_t width = grid[0].size();
    for (const std::vector<int>& row : grid) {
        // 앞에서 구한 행의 길이와 다른 행이 나타나면 유효하지 않다고 판정
        if (row.size() != width) {
            return false;
        }
    }

    // 검사를 통과하면 유효함
    return true;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid) const
{                                            // y             //x
    // 2차원 안에 잘 들어간 벡터값인지 검증
    // grid 는 가로 크기는 같다고 가정
    return x >= 0 && x < static_cast<int>(grid[0].size())
        && y >= 0 && y < static_cast<int>(grid.size()); // x: 너비, y: 높이

}

bool AStar::IsDiagonalBlocked(const Position& current, const Direction& direction, const std::vector<std::vector<int>>& grid) const
{
    // 이동하려는 방향에 장애물이 있는지 확인
    // 대각선 성분만 판단
    // 대각선 성분이 아니라면 판단할 필요 없음
    // 데이터적으로 대각선 어케 표현? 콘솔에서 위면 -1
    // 대각선 방향의 x,y 성분은 모두 0이 아니기 때문

    if (direction.x == 0 || direction.y == 0) {
        return false;
    }

    // 대각선으로 이동하려는 새로운 위치의 x 성분과 y 성분을 분해
    int sideX = current.x + direction.x;
    int sideY = current.y + direction.y;

    // 대각선 이동 성분 위치 중 하나라도 장애물(벽)이 있으면 이동 불가
    return grid[current.y][sideX] == (int)TileType::Wall ||
        grid[sideY][current.x] == (int)TileType::Wall;
}

/*
Node* AStar::FindOpenNode(int x, int y) const
{ // 순차 탐색
    // 같은 좌표의 노드를 openList에서 찾기
    for (Node* node : openList) {
        // 좌표 비교
        if (node->position == Position(x, y)) {
            return node;
        }
    }
    return nullptr;
}*/

bool AStar::IsInClosedList(int x, int y) const // 이미 방문한 노드면 무시
{
    // 같은 좌표가 ClosedList 에 있는지 확인
    for (Node* node : closedList) {
        // 좌표 비교
        if (node->position == Position(x, y)) {
            return true;
        }
    }
    return false;
}

bool AStar::IsDestination(const Node* node) const
{
    // 두 노드 모두 null이 아니고, 두 노드의 위치가 같은지 비교
    return (node != nullptr) && (goalNode != nullptr) && node->position == goalNode->position;
}

// 시각화할 때 필요한 2 함수
void AStar::ClearVisualization(std::vector<std::vector<int>>& grid) const
{
    // 탐색 후보 표시해둔 것을 다시 원상 복구
    // 최적의 경로 찾기위해 확인해본 곳들,
    // 탐색후보로 표시해두었다는건, 이동가능하다는 곳
    for (std::vector<int>& row : grid) {
        for (int& value : row) {
            if (value == (int)TileType::Visited) {
                value = (int)TileType::Ground;
            }
        }
    }

}

void AStar::DisplayGrid(std::vector<std::vector<int>>& grid) const
{   // 맵을 받아서 그리는 함수
    // 커서를 원점으로 이동시킬거임
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    static COORD origin = { 0,0 };
    SetConsoleCursorPosition(handle, origin);

    // 글자색
    int color = 1 << 0;
    int red = FOREGROUND_RED; // bit 연산으로 1<<0 이 red
    int green = FOREGROUND_GREEN;
    int white = red | green | FOREGROUND_BLUE;

    for (int y = 0; y < (int)grid.size(); ++y) {
        // 타일 값에 따라 글자 색상 및 글자 지정해서 출력
        for (int x = 0; x < (int)grid[y].size(); ++x) {
            if (grid[y][x] == (int)TileType::Start) {
                SetConsoleTextAttribute(handle, red);
                std::cout << "S ";
            }
            else if (grid[y][x] == (int)TileType::Goal) {
                SetConsoleTextAttribute(handle, red);
                std::cout << "G ";
            }
            else if (grid[y][x] == (int)TileType::Wall) {
                SetConsoleTextAttribute(handle, white);
                std::cout << "1 ";
            }
            else if (grid[y][x] == (int)TileType::Visited) {
                SetConsoleTextAttribute(handle, green);
                std::cout << "+ ";
            }
            else { // 이동 가능한 곳은 0
                SetConsoleTextAttribute(handle, white);
                std::cout << "0 ";
            }
        }
        // 한 라인 (행) 출력이 마우리 되면 개행 출력
        std::cout << "\n";
    }
}

