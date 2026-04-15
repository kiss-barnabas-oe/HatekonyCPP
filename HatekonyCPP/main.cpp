#include <iostream>
#include "BinaryTree.h"

int main()
{
	BinaryTree<int, std::string> tree;
	tree.Insert(1, "valami");
	try
	{
		tree.Insert(1, "valami2");
	}
	catch (const std::exception&)
	{
		std::cout << "Key already exists in the tree." << std::endl;
	}
	std::cout << *tree.Find(1) << std::endl;
	if(tree.Contains(1))
		std::cout << "Key " << 1 << " is in tree." << std::endl;	
}