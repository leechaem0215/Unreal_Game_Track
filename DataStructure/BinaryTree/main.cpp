#include "BinaryTree.h";
#include <string>
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	BinaryTree<std::string> tree("A");

	tree.AddLeftChild("A", "B");
	tree.AddRightChild("A", "C");

	tree.AddLeftChild("B", "D");
	tree.AddRightChild("B", "F");

	tree.AddLeftChild("C", "F");
	tree.AddRightChild("C", "G");


	std::cout << "삭제 전 중위 순회: \n";
	tree.InorderTraverse();

	if (tree.Remove("B"))
	{
		std::cout << "B 노드 제거 성공. 삭제 후 중위 순회: \n";
		tree.InorderTraverse();
	}
	else
	{
		std::cout << "삭제 실패\n";
	}

	// 검색
	if (tree.Find("Q"))
	{
		std::cout << "Q 검색 성공\n";
	}
	else
	{
		std::cout << "Q 검색 실패\n";
	}

}