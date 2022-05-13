#include "tree.h"

Tree::Tree()
{
	root = new Node();
}

Tree::~Tree()
{
	deleteNodes(this->root);
}

void Tree::printTree(Node* node) //访问顺序 根左右
{
	if (node != nullptr)
	{
		node->printContent();
		printTree(node->left);
		printTree(node->right);
	}
}

void Tree::deleteNodes(Node* node) //访问顺序 左右根
{
	if (node != nullptr)
	{
		deleteNodes(node->left);
		deleteNodes(node->right);
		//cout << "delete " << node->data << endl;
		// delete node;
		node = nullptr;
	}
}