#include "TreeNode.h"

TreeNode::TreeNode(Element& elem) : i(0) //elem_(&elem), i(0)
{
	elem_ = elem.clone();
	for (int k = 0; k < elem_->getNumberOfPins(); k++)
		inputs_.push_back(nullptr);
}

void TreeNode::addChild(TreeNode& child, int i)
{
	inputs_[i] = &child;
}

void TreeNode::addChild(TreeNode& in)
{
	inputs_.push_back(&in);
}

TreeNode* TreeNode::getCurrChild()
{
	return inputs_[i++];
}

TreeNode* TreeNode::getNChild(int i) const
{
	return inputs_[i];
}

int TreeNode::getNumOfChildren() const
{
	return elem_->getNumberOfPins();
}

int TreeNode::getNum() const
{
	return elem_->getNumber();
}

bool TreeNode::getOutput() const
{
	return elem_->getOutput();
}

int TreeNode::getID() const
{
	return elem_->getNumber();
}

void TreeNode::restartCounter()
{
	i = 0;
}

void TreeNode::calOutput()
{

	if (elem_->isGenerator()) return;

	elem_->setOutput(elem_->standardOutput()); //postavlja izlaz na standardni pocetni

	for (auto t: inputs_) //for prolazi kroz svu decu i racuna izlaz kao trenutni i/ili novi (u zavisnosti od operacije)
	{
		elem_->doing(t->elem_->getOutput());
	}
}

void TreeNode::changeGenerator()
{
	if(elem_->isGenerator())
		elem_->doing(!(elem_->getOutput()));
	return;
}

TreeNode::~TreeNode()
{
	delete elem_;

	for (auto i : inputs_)
	{
		i = nullptr;
	}
}
