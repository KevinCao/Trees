#ifndef AVLTREE_H
#define AVLTREE_H

#include <vector>

class AVLTree
{
	struct Node
	{
		Node(int value)
			:st_Value(value)
			,st_BF(0)
			,st_pLeftChild(0)
			,st_pRightChild(0)
		{

		}

		~Node()
		{
			if (0 != st_pLeftChild)
				delete st_pLeftChild;
			if (0 != st_pRightChild)
				delete st_pRightChild;
		}

		int st_Value;
		int st_BF;
		Node* st_pLeftChild;
		Node* st_pRightChild;
	};
public:
	AVLTree(void);
	~AVLTree(void);

public:
	void addNode(int value);
	void rmNode(int value);

private:
	std::vector<Node*> findInsertPath(int value)const;

	void updateBFForInsert(std::vector<Node*>& path);

	void adjustTreeForInsert(std::vector<Node*>& path);
private:
	Node* m_pRootNode;
};

#endif