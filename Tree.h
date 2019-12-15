#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include<vector>
#include<stack>

class Tree
{
public:

	Tree(vector<TreeNode*>);

	void interact(); //obilazi stablo i racuna stanja
	//void setItoZero(int i);

private:
	vector<TreeNode*> roots_;
};

#endif