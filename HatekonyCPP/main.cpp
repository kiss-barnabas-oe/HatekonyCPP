#include <iostream>
#include "binary_tree.h"

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
	if(tree.contains(1))
		std::cout << "Key " << 1 << " is in tree." << std::endl;
	std::cout << *tree[1] << std::endl;	
}