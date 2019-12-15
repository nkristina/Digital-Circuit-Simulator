#include "Tree.h"

Tree::Tree(vector<TreeNode*> roots)
{
	for (auto t : roots)
		roots_.push_back(t);
}

void Tree::interact()
{
	for (auto k : roots_)
	{
		stack<TreeNode*> unvisited;
		stack<int> index;
		int i = 0;
		TreeNode* curr = k, * last = nullptr;

		while (!unvisited.empty() || (curr!=nullptr && i <= (curr->getNumOfChildren())))
		{
			if (curr != nullptr && curr->getNumOfChildren() && i<(curr->getNumOfChildren()))
			{
				unvisited.push(curr);
				index.push(i+1);
				curr = curr->getNChild(i);
				i = 0;
			}
			else
			{
				if (!(curr->getNumOfChildren()))
				{
					curr = unvisited.top();
					i = index.top();
					index.pop();
					unvisited.pop();
				}
				else
				{
					if (i >= (curr->getNumOfChildren())) //proveri manje jednako
					{
						curr->calOutput();
						if (unvisited.size() != 0)
						{
							curr = unvisited.top();
							i = index.top();
							index.pop();
							unvisited.pop();
						}
						else
							curr = nullptr;
					}
					else
						return;
				}
			}
		}
	}
	return;
}

/*void Tree::interact()
{
	stack<TreeNode*> unvisited;

	for (auto k : roots_) //prolazak kroz sve sonde
	{
		TreeNode* curr = k, * last = nullptr;

		while (!unvisited.empty() || curr != nullptr)
		{
			if (curr != nullptr)
			{
				unvisited.push(curr);
				curr = curr->getCurrChild();
			}
			else
			{
				TreeNode* topNode = unvisited.top();
				TreeNode* next = topNode->getCurrChild();
				if (next != nullptr && next != last)
					curr = next;
				else
				{
					last = topNode;
					last->calOutput();
					unvisited.pop();
				}
			}
		}
	}
}*/

/* void Tree::setItoZero(int i)
{
	stack<TreeNode*> unvisited;
	TreeNode* curr = roots_[i], * last = nullptr;

	while (!unvisited.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			unvisited.push(curr);
			curr = curr->getCurrChild();
		}
		else
		{
			TreeNode* topNode = unvisited.top();
			TreeNode* next = topNode->getCurrChild();
			if (next != nullptr && next != last)
				curr = next;
			else
			{
				last = topNode;
				last->restartCounter();
				unvisited.pop();
			}
		}
	}
}*/
