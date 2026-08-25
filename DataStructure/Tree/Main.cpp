#include "Tree.h"
#include <iostream>
#include <string>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 트리 생성.
	Tree<std::string> tree("A");

	// 자손 노드 추가.
	tree.AddChild("A", "B");
	tree.AddChild("A", "C");
	tree.AddChild("A", "D");

	tree.AddChild("B", "E");
	tree.AddChild("B", "F");
	tree.AddChild("B", "G");

	tree.AddChild("C", "H");

	tree.AddChild("D", "I");
	tree.AddChild("D", "J");

	// 삭제 처리

	if (tree.Remove("C"))
	{
		std::cout << "삭제 성공\n";
	}
	else
	{
		std::cout << "삭제 실패\n";
	}
}