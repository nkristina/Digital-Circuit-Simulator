#ifndef TREENODES_H
#define TREENODES_H

#include "Element.h"

using namespace std;

class TreeNode
{
public:
	TreeNode(Element& elem);
	TreeNode(const TreeNode&) = delete;
	TreeNode(TreeNode&&) = delete;

	void addChild(TreeNode&, int); //dodavanje deteta na cvor
	void addChild(TreeNode&);

	TreeNode* getCurrChild(); //vraca trenutno dete i prelazi na sledece
	TreeNode* getNChild(int) const; //vraca N-to dete
	int getNumOfChildren() const; //vraca broj ulaza
	
	int getNum() const; //vraca redni beoj elementa
	bool getOutput() const; //vraca stanje elementa
	int getID() const; //vraca ID elementa

	void restartCounter();

	void calOutput();
	void changeGenerator();

	~TreeNode();

private:
	Element* elem_;
	int i; //brojac koje je trenutno dete
	vector<TreeNode*> inputs_; //niz ulaza
};

#endif