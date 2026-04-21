#include <iostream>
#include "binary_tree.h"

int main()
{
	BinaryTree<int, std::string> tree;
	tree.insert(1, "valami");
	if(!tree.insert(1, "valami2"))
		std::cout << "Key " << 1 << " already exists." << std::endl;
		
	if(tree.contains(1))
		std::cout << "Key " << 1 << " is in tree." << std::endl;
	std::cout << *tree[1] << std::endl;	
}