#include "tree.h"

Tree::Tree()
{
	root = new Node();
}

Tree::~Tree()
{
	deleteNodes(this->root);
}

void Tree::printTree(Node* node) //·ÃÎÊË³Ðò ¸ù×óÓÒ
{
	if (node != nullptr)
	{
		node->printContent();
		printTree(node->left);
		printTree(node->right);
	}
}

void Tree::deleteNodes(Node* node) //·ÃÎÊË³Ðò ×óÓÒ¸ù
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