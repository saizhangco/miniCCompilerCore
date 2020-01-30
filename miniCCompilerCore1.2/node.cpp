#include "node.h"

void Node::printContent()
{
	cout << data << endl;
}

bool Node::addLeftChild(string data)
{
	this->left = new Node();
	this->left->data = data;
	return true;
}
bool Node::addRightChild(string data)
{
	this->right = new Node();
	this->right->data = data;
	return true;
}

void Node::addChildToRoot(Node* node)
{

	if (!this->left) //左结点为空
	{
		this->left = node;
		//this->left->data = data;
	}
	else //左结点不为空
	{
		Node* tmp;
		tmp = this->left;
		while (tmp->right)
		{
			tmp = tmp->right;
		}
		tmp->right = node;
	}
}